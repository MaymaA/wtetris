wtetris
=======

A simple OpenGL tetris game, written in C.

---------------------------------------------------------------

Video for the text averse: http://www.youtube.com/watch?v=vWmDVjVb9eM

Why tetris, and why in C? Well, because everyone still likes tetris, and because writing any game in C is considered to be challenging. Although, for anyone who actually knows C fairly well, I think the word "tedious" would be more descriptive.

In either case, the tetris game itself is only a few files, the largest of which is no longer than 364 lines. There is quite a bit of boiler-plate code in the nglu directory, but it's still fairly manageable (in my opinion).

All the geometry in the game (the cube, and the characters used for basic text) were exported from blender, using [glrawd](https://github.com/GoranM/glrawd). The relevant .blend ships with this project (scene.blend), so feel free to take a look.

Dependencies
------------

* SDL
* OpenGL
* GLEW

Compilation
-----------

CMake is the build system used, so be sure to get that first, and then do the following, in the same directory where wtetris was stored:

```
mkdir build_wtetris
cd build_wtetris
cmake ../wtetris
make
```

Assuming successful compilation, you should be able to run the resulting program with `./wtetris`.
