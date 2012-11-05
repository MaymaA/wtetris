#include "system/events.h"
#include "system/keyboard.h"
#include "system/mouse.h"
#include "SDL.h"

static SDL_Event event;

static void process(){

	keyboard.update();
	mouse.update();

	while ( SDL_PollEvent(&event) ){

		switch (event.type){

			case SDL_KEYDOWN:
				keyboard.key_state[ event.key.keysym.sym ] = keyboard.KEY_HIT;
				break;

			case SDL_KEYUP:
				keyboard.key_state[ event.key.keysym.sym ] = keyboard.KEY_UP;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouse.btn_state[ event.button.button - 1 ] = mouse.BTN_HIT;
				break;

			case SDL_MOUSEBUTTONUP:
				mouse.btn_state[ event.button.button - 1 ] = mouse.BTN_UP;
				break;

			case SDL_MOUSEMOTION:
				mouse.pos[0] = event.motion.x;
				mouse.pos[1] = event.motion.y;
				break;

			case SDL_QUIT:
				printf("Quitting\n");
				exit(0);
		}
	}

}

struct _events events = {
	.process = process
};
