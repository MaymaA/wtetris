#include "system/display.h"
#include <GL/glew.h>

static void create(short width, short height){

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	display.screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);

	glewInit();
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

static void update(){

	SDL_GL_SwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

static int getWidth(){

	return display.screen->w;

}

static int getHeight(){

	return display.screen->h;

}



struct _display display =
{
	.create = create,
	.update = update,
	
	.getWidth = getWidth,
	.getHeight = getHeight
};
