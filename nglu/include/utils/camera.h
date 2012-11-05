#ifndef NGLU_CAMERA
#define NGLU_CAMERA

#include "utils/gl.h"

typedef struct{
	GLint loc_proj;
	GLint loc_view;
	float mat_world[16];
	float mat_view[16];
	float mat_proj[16];
} Camera;


void cameraWorldToView(Camera* cam);

#endif
