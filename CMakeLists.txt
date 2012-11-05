cmake_minimum_required (VERSION 2.6)

project(wtetris)

set(NGLU_PROJ_DIR ${PROJECT_SOURCE_DIR}/nglu)

add_subdirectory(${NGLU_PROJ_DIR})

set(CMAKE_MODULE_PATH ${NGLU_PROJ_DIR}/cmake_modules)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
	${OPENGL_INCLUDE_DIR}
	${SDL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
	${NGLU_PROJ_DIR}/include
	include)

link_directories(../build_wtetris/nglu/source)

file(GLOB_RECURSE SRC source/*.c)
set(CMAKE_C_FLAGS "-Wall -lm")

add_executable(wtetris ${SRC})
target_link_libraries(wtetris nglu
	${SDL_LIBRARY} 
	${OPENGL_gl_LIBRARY}
	${GLEW_LIBRARY})
