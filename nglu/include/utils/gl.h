#ifndef NGLU_GL
#define NGLU_GL

#include <GL/glew.h>

struct _gl{
	GLuint (*createShader)(GLenum shader_type, const char* shader_source);
	GLuint (*createProgram)(GLuint vs, GLuint fs);
};

extern struct _gl gl;

#endif
