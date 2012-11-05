#include "system/mouse.h"
#include "SDL.h"

static void update(){

	const short btn_count = 3;
	short i = 0;

	for ( ; i < btn_count; ++i){
		if ( mouse.btn_state[i] == mouse.BTN_HIT ){
			mouse.btn_state[i] = mouse.BTN_DOWN;
		}
	}

}

static char btnHit(short btn){

	return mouse.btn_state[btn] == mouse.BTN_HIT;

}

static char btnDown(short btn){

	return mouse.btn_state[btn] == mouse.BTN_DOWN;

}

static void setPos(unsigned short x, unsigned short y){

	SDL_WarpMouse(x, y);

}

static void show(){

	SDL_ShowCursor(SDL_ENABLE);

}

static void hide(){

	SDL_ShowCursor(SDL_DISABLE);

}


struct _mouse mouse = {
	.BTN_UP = 0,
	.BTN_HIT = 1,
	.BTN_DOWN = 2,

	.LEFT = 0,
	.MIDDLE = 1,
	.RIGHT = 2,

	.update = update,

	.btnHit = btnHit,
	.btnDown = btnDown,

	.setPos = setPos,

	.show = show,
	.hide = hide
};
