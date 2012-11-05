#include "wave.h"

void waveLocsSet(Wave* wave, GLuint prog){

	wave->locs[0] = glGetUniformLocation(prog, "wave.src");
	wave->locs[1] = glGetUniformLocation(prog, "wave.amp");
	wave->locs[2] = glGetUniformLocation(prog, "wave.wlen");
	wave->locs[3] = glGetUniformLocation(prog, "wave.time");
}


void wavePosSet(Wave* wave, Piece* piece){

	wave->src[0] = piece->coords[0][1] * 2;
	wave->src[1] = piece->coords[0][0] * -2;
	wave->src[2] = 0;

}


void waveToProg(Wave* wave){


	glUniform3fv(wave->locs[0], 1, wave->src);
	glUniform1f(wave->locs[1], wave->amp);
	glUniform1f(wave->locs[2], wave->wlen);
	glUniform1f(wave->locs[3], wave->time);

}
