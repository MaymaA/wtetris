#ifndef WTET_WAVE_H
#define WTET_WAVE_H

#include "utils/gl.h"
#include "board.h" // Piece

typedef struct{
	GLint locs[4];
	float src[3];
	float amp;
	float wlen;
	float time;
} Wave;

void waveLocsSet(Wave* wave, GLuint prog);
void wavePosSet(Wave* wave, Piece* piece);
void waveToProg(Wave* wave);

#endif
