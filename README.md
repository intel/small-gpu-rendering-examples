# Small GPU rendering examples

Pieces of C++ and OpenGL code for learning and experimenting. Some of the code
was created with the help of the tutorial on https://open.gl.


## Building from source

You will need at least OpenGL 3.2 and Linux (tested on Ubuntu Trusty).

    $ glxinfo|grep "OpenGL core profile version"  # should be at least 3.2
    $ sudo apt-get install cmake clang libsdl2-dev

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ ./bin/main

Currently it should just display a simple triangle.
Installation is not supported (and probably never will be, these are just
experiments).
