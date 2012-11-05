#ifndef NGLU_MOUSE
#define NGLU_MOUSE

struct _mouse{
	char btn_state[3];
	unsigned short pos[2];

	// Button states
	char BTN_UP;
	char BTN_HIT;
	char BTN_DOWN;

	// Button constants
	int LEFT;
	int MIDDLE;
	int RIGHT;

	void (*update)();

	char (*btnHit)(short btn);
	char (*btnDown)(short btn);

	void (*setPos)(unsigned short x, unsigned short y);

	void (*show)();
	void (*hide)();

};

extern struct _mouse mouse;

#endif
