DISCONTINUATION OF PROJECT.

This project will no longer be maintained by Intel.

Intel has ceased development and contributions including, but not limited to, maintenance, bug fixes, new releases, or updates, to this project. 

Intel no longer accepts patches to this project.

If you have an ongoing need to use this project, are interested in independently developing it, or would like to maintain patches for the open source software community, please create your own fork of this project. 
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
    $ ./bin/tutorial

Currently it should just display a simple triangle. For other examples, look
into the `build/bin/` directory. But be careful, some of them show off a driver
bug. A binary called `foo` is going to be created from the directory called
`foo`, you can look there to find out what is the expected behavior.

Installation is not supported (and probably never will be, these are just
experiments).
