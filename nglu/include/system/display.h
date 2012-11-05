#ifndef NGLU_DISPLAY
#define NGLU_DISPLAY

#include "SDL.h"

struct _display{
	SDL_Surface* screen;
	void (*create)(short width, short height);
	void (*update)();
	int (*getWidth)();
	int (*getHeight)();
};

extern struct _display display;

#endif
