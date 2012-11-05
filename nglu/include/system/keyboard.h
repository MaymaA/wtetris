#ifndef NGLU_KEYBOARD
#define NGLU_KEYBOARD

struct _keyboard{

	char key_state[322];

	// Key states (used by events.h:process)
	char KEY_UP;
	char KEY_HIT;
	char KEY_DOWN;

	// Key constants
	short UP;
	short DOWN;
	short RIGHT;
	short LEFT;

	void (*update)();
	char (*keyHit)(short key);
	char (*keyDown)(short key);

};

extern struct _keyboard keyboard;

#endif
