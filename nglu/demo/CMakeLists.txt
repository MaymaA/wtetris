file(GLOB_RECURSE SRC *.c)

add_executable(demo ${SRC})
target_link_libraries(demo nglu)
