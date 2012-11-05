#ifndef NGLU_TIMER
#define NGLU_TIMER

#include "SDL.h"

typedef struct {
	float time;
	Uint32 tick;
	int count;
} Timer;


void timerInit(Timer* timer, float time);
int timerTick(Timer* timer);

#endif
