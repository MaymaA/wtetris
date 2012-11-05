#include "board.h"

#include "utils/math.h"
#include "utils/rawdimp.h"
#include "SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void boardRowSet(Board* board, int row, Block* block){

	int i;
	for (i = 0; i < board->count_cols; ++i){
		board->grid[row][i] = block;
	}
}

static Geom* geomGet(void* object){

	Board* board = (Board*)object;

	static int i = 0;
	static int j = 0;

	Block* block;
	char* rows_hidden = board->rows_hidden;

	float* pos;

	for (; i < board->count_rows; ++i){

		if (rows_hidden[i])
			continue;

		for (; j < board->count_cols; ++j){

			block = board->grid[i][j];

			if (block){

				pos = &block->geom->mat_world[12];
				pos[1] = i * -2; pos[0] = j * 2;

				if (++j == board->count_cols){
					++i;
					j = 0;
				}

				return block->geom;


			}


		}
	}

	i = j = 0;
	return NULL;
}

void boardClear(Board* board){

	Block*** grid = board->grid;

	int i;
	for (i = 1; i < board->count_rows - 1; ++i){
		memset(grid[i] + 1, 0, sizeof(Block**) * (board->count_cols - 2));
	}
}

void boardInit(Board* board, Geom* geom_base, int count_rows, int count_cols){

	srand(SDL_GetTicks());

	Block*** grid = (Block***)malloc(sizeof(Block**) * count_rows);

	board->geomGet = geomGet;

	board->count_rows = count_rows;
	board->count_cols = count_cols;

	board->geom_base = geom_base;

	Block* border = (Block*)malloc(sizeof(Block));
	border->geom = geom_base;

	int i;
	for (i = 0; i < count_rows; ++i){
		grid[i] = (Block**)malloc(sizeof(Block**) * count_cols);
		memset(grid[i], 0, sizeof(Block**) * count_cols);
		grid[i][0] = border;
		grid[i][count_cols-1] = border;
	}


	board->grid = grid;

	board->rows_hidden = (char*)malloc(count_rows);
	memset(board->rows_hidden, 0, count_rows);

	boardRowSet(board, 0, border);
	boardRowSet(board, count_rows - 1, border);

	boardPieceNew(board);

}


static void pieceCoordsFill(Board* board, Block* block){

	Block*** grid = board->grid;
	Piece* piece = &board->piece;

	int i, r, c;
	for (i = 0; i < 4; ++i){
		r = piece->coords[i][0];
		c = piece->coords[i][1];
		grid[r][c] = block;
	}

}


static void boardPieceEngrave(Board* board){

	pieceCoordsFill(board, board->piece.base);
}

static void boardPieceErase(Board* board){

	pieceCoordsFill(board, NULL);

}

int boardPieceNew(Board* board){

	int ptypes[7][4][2] = {
		{{0,0}, {0,-1}, {0,1}, {1,0}},   // T
		{{0,0}, {-1,0}, {1,0}, {-2,0}},  // Line
		{{0,0}, {0,1}, {1,0}, {1,1}},    // Cube
		{{0,0}, {-1,0}, {1,0}, {1,1}},   // L
		{{0,0}, {-1,0}, {1,0}, {-1,1}},  // rev L 
		{{0,0}, {-1,0}, {0,1}, {1,1}},   // 4
		{{0,0}, {-1,0}, {0,-1}, {1,-1}} // rev 4
	};

	int pt = rand() % 7;

	Block*** grid = board->grid;
	Block* block;
	Piece* piece = &board->piece;
	piece->base = board->grid[0][0];
	
	int i;
	int* r;
	int* c;
	for (i = 0; i < 4; ++i){
		r = &piece->coords[i][0];
		c = &piece->coords[i][1];
		*r = ptypes[pt][i][0] + 3;
		*c = ptypes[pt][i][1] + 5;
		block = grid[*r][*c];
		if ( block )
			return 0;
	}

	boardPieceEngrave(board);

	return 1;
	
}



static int rowIsComplete(Block** row, int len_row){

	int i;
	for (i = 0; i < len_row; ++i){
		if ( ! row[i] )
			return 0;
	}

	return 1;

}

int boardCompleteRows(Board* board){

	int i, complete = 0;
	for (i = 1; i < board->count_rows - 1; ++i){
		if (rowIsComplete(board->grid[i], board->count_cols)){
			++complete;
		}
	}

	return complete;
}

static void boardCompress(Board* board, int row){

	Block*** grid = board->grid;

	int i;
	for (i = row; i > 1; --i)
		memcpy(grid[i], grid[i-1], board->count_cols * sizeof(Block**));

}

void boardClearComplete(Board* board){

	int i;
	for (i = 1; i < board->count_rows - 1; ++i){
		if (rowIsComplete(board->grid[i], board->count_cols))
			boardCompress(board, i);
	}
}

void boardPieceMove(Board* board, int rel_row, int rel_col){

	boardPieceErase(board);

	Piece* piece = &board->piece;
	
	int i;
	for (i = 0; i < 4; ++i){
		piece->coords[i][0] += rel_row;
		piece->coords[i][1] += rel_col;
	}

	boardPieceEngrave(board);
}


static void pieceRotate(Piece* piece, float angle){

	float mat_rot[16];
	matRot(mat_rot, angle, 2);

	float vec[4]; 

	int* coords = (int*)piece->coords;
	int* pivot = coords;
	int* coord;

	int i;
	for (i = 1; i < 4; ++i){
		coord = coords + (i * 2);
		vec[0] = coord[0] - pivot[0];
		vec[1] = coord[1] - pivot[1];
		matMulVec(mat_rot, vec, vec);
		coord[0] = pivot[0] + floatToInt(vec[0]);
		coord[1] = pivot[1] + floatToInt(vec[1]);
	}

}

int boardPieceCanRotate(Board* board){

	Block*** grid = board->grid;
	Piece* piece = &board->piece;

	boardPieceErase(board);

	pieceRotate(piece, 3.1415/2);

	int can_rotate = 1;

	int i, r, c;
	for (i = 0; i < 4; ++i){
		r = piece->coords[i][0];
		c = piece->coords[i][1];

		if (r < 1 || r > board->count_rows - 2 || 
			c < 1 || c > board->count_cols - 2 ||
			grid[r][c]){

			can_rotate = 0;
			break;
		}

	}

	pieceRotate(piece, -3.1415/2);

	boardPieceEngrave(board);

	return can_rotate;
}



void boardPieceRotate(Board* board){

	boardPieceErase(board);
	
	pieceRotate(&board->piece, 3.1415/2);

	boardPieceEngrave(board);

}

void boardPieceDrop(Board* board){

	while ( boardPieceCanMove(board, 1, 0) )
		boardPieceMove(board, 1, 0);

}


int coordInCoords(int coord[], int coords[][2], int count_coords){

	int i;
	for (i = 0; i < count_coords; ++i){
		if (coord[0] == coords[i][0] && coord[1] == coords[i][1]){
			return 1;
		}
	}

	return 0;
}

int boardPieceCanMove(Board* board, int rel_row, int rel_col){

	Block*** grid = board->grid;
	Piece* piece = &board->piece;
	Block* block;

	int i;
	int coord[2];
	for (i = 0; i < 4; ++i){

		coord[0] = piece->coords[i][0] + rel_row;
		coord[1] = piece->coords[i][1] + rel_col;
		block = grid[coord[0]][coord[1]];

		if ( block && ! coordInCoords(coord, piece->coords, 4) ){
			return 0;
		}
	}

	return 1;
}


void boardCompleteRowsHide(Board* board){

	Block*** grid = board->grid;
	char* rows_hidden = board->rows_hidden;
	int len_row = board->count_cols;

	int i;
	for (i = 1; i < board->count_rows - 1; ++i){
		if ( rowIsComplete(grid[i], len_row) ){
			rows_hidden[i] = 1;
		}
	}

}


void boardHiddenRowsShow(Board* board){

	memset(board->rows_hidden, 0, board->count_rows);
}



