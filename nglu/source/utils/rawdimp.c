#include "utils/rawdimp.h"
#include "utils/file.h"

GLuint* rawdimp(const char* file_path, GLuint bo_vertex, GLuint bo_index){

	GLuint* count_verts = (GLuint*)file.load(file_path);
	GLfloat* verts = (GLfloat*)(count_verts + 1);
	GLuint* count_indices = (GLuint*)(verts + (*count_verts * 3));
	GLuint* indices = count_indices + 1;
	GLuint* count_nodes = indices + *count_indices;

	glBindBuffer(GL_ARRAY_BUFFER, bo_vertex);
	glBufferData(GL_ARRAY_BUFFER, *count_verts * 3 * sizeof(GLfloat), verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, *count_indices * sizeof(GLuint), indices, GL_STATIC_DRAW);

	return count_nodes;

}
