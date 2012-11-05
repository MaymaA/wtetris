#include "utils/camera.h"
#include "utils/math.h"
#include <string.h>

void cameraWorldToView(Camera* cam){

	float vec_pos[4];
	memcpy(vec_pos, &cam->mat_world[12], sizeof(vec_pos));
	memset(&cam->mat_world[12], 0, sizeof(float) * 3);

	memcpy(cam->mat_view, cam->mat_world, sizeof(float) * 16);
	memcpy(&cam->mat_world[12], vec_pos, sizeof(vec_pos));

	matTranspose(cam->mat_view);
	vecMul(vec_pos, -1); vec_pos[3] = 1;
	matMulVec(cam->mat_view, vec_pos, vec_pos);

	memcpy(&cam->mat_view[12], vec_pos, sizeof(vec_pos));

}
