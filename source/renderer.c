#include "renderer.h"
#include "utils/math.h" 

void render(Renderer* renderer, Scene* scene){

	GLint loc_world = renderer->loc_world;

	Array* objects = scene->objects;

	void* obj;
	Geom* (*geomGet)(void* object);
	Geom* geom = NULL;

	int i;
	for (i = 0; i < objects->idx; ++i){

		obj = objects->data[i];
		geomGet = (Geom* (*)(void*))((void**)obj)[0];

		while ( (geom = geomGet(obj)) ){

			glUniformMatrix4fv(loc_world, 1, 0, geom->mat_world);

			glDrawElements(
				GL_TRIANGLES, 
				geom->count_idx,
				GL_UNSIGNED_INT,
				(GLvoid*)(sizeof(GLuint) * geom->offset_idx)
			);
		}

	}
}

void toggleProjection(Camera* cam){

	static int mode = 0;
	float ar = 640.f/480;

	if ( (mode = ! mode) ){
		matProjection(cam->mat_proj, 60, 640.f/480, 1, 1000);
	}else{
		matOrtho(cam->mat_proj, -25 * ar, 25 * ar, -25, 25, 1, 1000);
	}

	glUniformMatrix4fv(cam->loc_proj, 1, 0, cam->mat_proj);
}
