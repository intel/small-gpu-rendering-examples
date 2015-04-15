cmake_minimum_required(VERSION 2.8)
project(OpenGL)

find_package(GLUT)
find_package(OpenGL)
INCLUDE(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)

set(CMAKE_CXX_FLAGS "-g -Wall")

include_directories(${SDL2_INCLUDE_DIRS})
set(CORELIBS  ${SDL2_LIBRARIES} ${OPENGL_LIBRARY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
