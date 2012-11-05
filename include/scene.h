#ifndef WTET_SCENE_H
#define WTET_SCENE_H

#include "utils/contain.h"
#include "utils/camera.h"
#include "wave.h"

typedef struct{
	Camera* cam;
	Wave* wave;
	Array* objects;
	void (*state)();
} Scene;

#endif
