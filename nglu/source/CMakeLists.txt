file(GLOB_RECURSE SRC *.c)

add_library(nglu SHARED ${SRC})
target_link_libraries(nglu 
	${SDL_LIBRARY} 
	${OPENGL_gl_LIBRARY}
	${GLEW_LIBRARY})
