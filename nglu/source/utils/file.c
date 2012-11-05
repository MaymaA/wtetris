#include "utils/file.h"

#include <stdlib.h>

static char* load(const char* path){

	FILE* fp = fopen(path, "rb");

	size_t file_size = file.size(fp);

	char* data = malloc(file_size);
	fread(data, sizeof(char), file_size, fp);

	fclose(fp);

	return data;

}

static char* loadText(const char* path){

	FILE* fp = fopen(path, "rb");

	size_t file_size = file.size(fp);
	
	char* data = malloc(file_size);
	fread(data, sizeof(char), file_size, fp);

	fclose(fp);

	data[file_size] = '\0';

	return data;

}

static size_t size(FILE* fp){

	size_t pos = ftell(fp);
	size_t file_size;

	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0, pos);

	return file_size;

}

struct _file file = 
{
	.load = load,
	.loadText = loadText,
	.size = size
};
