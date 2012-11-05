#ifndef WTET_BOARD_H
#define WTET_BOARD_H

#include "utils/gl.h"
#include "utils/rawdimp.h"


typedef struct{
	Geom* geom;
} Block;

typedef struct{
	int coords[4][2];
	Block* base;
} Piece;

typedef struct{
	Geom* (*geomGet)(void* object);
	int count_rows;
	int count_cols;
	Geom* geom_base;
	Piece piece;
	Block*** grid;
	char* rows_hidden;
} Board;



void boardClear(Board* board);
void boardInit(Board* board, Geom* border, int count_rows, int count_cols);

int boardPieceNew(Board* board);

int boardCompleteRows(Board* board);
void boardClearComplete(Board* board);
void boardPieceMove(Board* board, int rel_row, int rel_col);
int boardPieceCanMove(Board* board, int rel_row, int rel_col);
int boardPieceCanRotate(Board* board);
void boardPieceRotate(Board* board);
void boardPieceDrop(Board* board);

void boardCompleteRowsHide(Board* board);
void boardHiddenRowsShow(Board* board);


#endif
