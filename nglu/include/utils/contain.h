#ifndef WTET_CONTAIN_H
#define WTET_CONTAIN_H

typedef struct{
	void** data;
	unsigned int capacity;
	unsigned int idx;
} Array;

void arrayInit(Array* array, unsigned int capacity);
void arrayAppend(Array* array, void* object);
void* arrayPop(Array* array);

#endif
