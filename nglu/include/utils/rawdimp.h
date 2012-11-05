#ifndef NGLU_RAWDIMP
#define NGLU_RAWDIMP

#include <GL/glew.h>

typedef struct {
	float mat_world[16];
	GLuint offset_idx;
	GLuint count_idx;
} Geom;

GLuint* rawdimp(const char* file_path, GLuint bo_vertex, GLuint bo_index);

#endif
