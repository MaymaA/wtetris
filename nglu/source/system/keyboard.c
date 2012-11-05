#include "system/keyboard.h"
#include <stdio.h>
#include <stdlib.h>


static void update(){

	const short key_count = 322;
	short i = 0;

	for ( ; i < key_count; ++i){
		if ( keyboard.key_state[i] == keyboard.KEY_HIT ){
			keyboard.key_state[i] = keyboard.KEY_DOWN;
		}
	}

}

static char keyHit(short key){

	return keyboard.key_state[key] == keyboard.KEY_HIT;

}

static char keyDown(short key){

	return keyboard.key_state[key] == keyboard.KEY_DOWN;

}
	


struct _keyboard keyboard = 
{
	.update = update,

	.KEY_UP = 0,
	.KEY_HIT = 1,
	.KEY_DOWN = 2,

	.UP = 273,
	.DOWN = 274,
	.RIGHT = 275,
	.LEFT = 276,

	.keyHit = keyHit,
	.keyDown = keyDown
};
