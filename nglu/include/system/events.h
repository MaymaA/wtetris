#ifndef NGLU_EVENTS
#define NGLU_EVENTS

struct _events {
	void (*process)();
};

extern struct _events events;

#endif
