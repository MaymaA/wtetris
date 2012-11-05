#include "utils/contain.h"
#include <stdlib.h>

void arrayInit(Array* array, unsigned int capacity){

	array->data = malloc(capacity * sizeof(void*));
	array->capacity = capacity;
	array->idx = 0;
	
}

void arrayAppend(Array* array, void* object){

	if (array->idx == array->capacity){
		array->data = realloc(array->data, (array->capacity *= 2) * sizeof(void*));
	}

	array->data[array->idx++] = object;
}

void* arrayPop(Array* array){

	return array->data[array->idx--];
}
