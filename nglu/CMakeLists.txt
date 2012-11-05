cmake_minimum_required (VERSION 2.6)

project(nglu)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
	${OPENGL_INCLUDE_DIR}
	${SDL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
	include)

set(CMAKE_C_FLAGS "-Wall -lm")

add_subdirectory(source)
add_subdirectory(demo)
