#include "utils/timer.h"

void timerInit(Timer* timer, float time){

	timer->time = time;
	timer->tick = 0;
	timer->count = 0;
}

int timerTick(Timer* timer){

	Uint32 delta = SDL_GetTicks() - timer->tick;

	if (delta > timer->time * 1000){
		timer->tick = SDL_GetTicks();
		timer->count += 1;
		return 1;
	}

	return 0;
	

}
