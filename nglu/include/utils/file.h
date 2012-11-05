#ifndef NGLU_FILE
#define NGLU_FILE

#include <stdio.h> // FILE
#include <string.h> // size_t

struct _file{
	char* (*load)(const char* path);
	char* (*loadText)(const char* path);
	size_t (*size)(FILE* fp);
};

extern struct _file file;

# endif
