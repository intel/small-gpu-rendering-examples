cmake_minimum_required(VERSION 2.8)
project(OpenGL)
set(CMAKE_CXX_COMPILER "clang++")

find_package(GLUT)
find_package(OpenGL REQUIRED) # GLU
find_package(GLEW REQUIRED)
INCLUDE(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
set(CORELIBS ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
