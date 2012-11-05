#include "system/events.h"
#include "system/display.h"
#include "system/keyboard.h"
#include "system/mouse.h"
#include "utils/file.h"
#include "utils/gl.h"
#include "utils/math.h"
#include "utils/camera.h"
#include "utils/rawdimp.h"
#include "fpscont.h"
#include <stdio.h>


int main(int argc, char* argv[]){

	display.create(640, 480);


	// Vertex and Index buffer objects
	//
	GLuint bo_vertex, bo_index;
	glGenBuffers(1, &bo_vertex);
	glGenBuffers(1, &bo_index);

	
	// Import data from a simple scene
	//
	GLuint* count_nodes = rawdimp("scene.rawd", bo_vertex, bo_index);
	Geom* nodes = (Geom*)(count_nodes + 1);


	// Create and load shader programs
	//
	char* src_vs = file.loadText("base.vs");
	char* src_fs = file.loadText("base.fs");

	GLuint vs = gl.createShader(GL_VERTEX_SHADER, src_vs);
	GLuint fs = gl.createShader(GL_FRAGMENT_SHADER, src_fs);

	GLuint program = gl.createProgram(vs, fs);

	glUseProgram(program);


	// Get handle to shader vars
	//
	GLint loc_world = glGetUniformLocation(program, "world");
	GLint loc_view = glGetUniformLocation(program, "view");
	GLint loc_proj = glGetUniformLocation(program, "proj");
	

	Camera cam;
	matIdent(cam.mat_world);
	matProjection(cam.mat_proj, 60, 640.f/480, 1, 1000);

	glUniformMatrix4fv(loc_proj, 1, 0, cam.mat_proj);

	mouse.hide();
	mouse.setPos(display.getWidth()/2, display.getHeight()/2);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_LINE);

	while (1){

		events.process();

		if (keyboard.keyHit('q')){
			break;
		}
		
		fpscont(&cam);

		glUniformMatrix4fv(loc_view, 1, 0, cam.mat_view);

		int i;
		Geom* node;
		for (i = 0; i < *count_nodes; ++i){
		      
		      node = nodes + i;

		      glUniformMatrix4fv(loc_world, 1, 0, node->mat_world);

		      glDrawElements(GL_TRIANGLES, node->count_idx, GL_UNSIGNED_INT, (GLvoid*)(node->offset_idx * sizeof(GLuint)));

		}

		display.update();


		SDL_Delay(16);
	}

	return 0;

}
