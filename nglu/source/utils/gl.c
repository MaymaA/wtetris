#include "utils/gl.h"
#include <stdio.h>
#include <stdlib.h>


static GLuint createShader(GLenum shader_type, const char* shader_source){

	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE){
		GLint log_len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);

		GLchar* log = malloc(log_len + 1);
		glGetShaderInfoLog(shader, log_len, NULL, log);

		const char* str_shader_type = NULL;
		switch(shader_type){
			case GL_VERTEX_SHADER: str_shader_type = "vertex"; break;
			case GL_FRAGMENT_SHADER: str_shader_type = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", str_shader_type, log);
		free(log);
	}

	return shader;
}


static GLuint createProgram(GLuint vs, GLuint fs){

	GLuint program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE){
		GLint log_len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);

		GLchar* log = malloc(log_len + 1);
		glGetProgramInfoLog(program, log_len, NULL, log);
		fprintf(stderr, "Linker failure: %s\n", log);
		free(log);
	}


	glDetachShader(program, vs);
	glDetachShader(program, fs);

	return program;
}

struct _gl gl = {
	.createShader = createShader,
	.createProgram = createProgram
};
