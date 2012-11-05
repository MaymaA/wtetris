#ifndef WTET_RENDERER_H
#define WTET_RENDERER_H

#include "utils/gl.h"
#include "utils/rawdimp.h"
#include "utils/camera.h"
#include "scene.h"

typedef struct {
	GLint loc_world;
} Renderer;

void render(Renderer* renderer, Scene* scene);
void toggleProjection(Camera* cam);

#endif
