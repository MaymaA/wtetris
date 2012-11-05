#include "system/keyboard.h"
#include "system/mouse.h"
#include "system/display.h"
#include "utils/math.h"
#include "fpscont.h"
#include <stdio.h>
#include <string.h>

void fpscont(Camera* cam){

	// Rip out position
	//
	float vec_pos[4];
	float* mat_world = cam->mat_world;
	memcpy(vec_pos, &mat_world[12], sizeof(vec_pos));
	memset(&mat_world[12], 0, sizeof(float) * 3);


	// Mouse-look
	//
	short center_x = display.getWidth()/2;
	short center_y = display.getHeight()/2;

	short delta_x = mouse.pos[0] - center_x;
	short delta_y = mouse.pos[1] - center_y;
	mouse.setPos(center_x, center_y);

	float mat_rotx[16];
	matRot(mat_rotx, delta_y * -0.001f, 0);
	matMul(mat_world, mat_rotx, mat_world);

	float mat_roty[16];
	matRot(mat_roty, delta_x * -0.001f, 1);
	matMul(mat_roty, mat_world, mat_world);


	// Movement
	//
	char up_down = keyboard.keyDown('w') - keyboard.keyDown('s');
	char right_left = keyboard.keyDown('d') - keyboard.keyDown('a');

	float speed = 0.5;
	float vec_vel[4];
	vec_vel[0] = right_left * speed;
	vec_vel[1] = 0;
	vec_vel[2] = -up_down * speed;
	vec_vel[3] = 1;

	matMulVec(mat_world, vec_vel, vec_vel);

	vecAdd(vec_pos, vec_vel, vec_pos); vec_pos[3] = 1;

	memcpy(cam->mat_view, cam->mat_world, sizeof(float) * 16);
	memcpy(&cam->mat_world[12], vec_pos, sizeof(vec_pos));

	cameraWorldToView(cam);



}
