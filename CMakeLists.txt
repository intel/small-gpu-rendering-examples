cmake_minimum_required(VERSION 2.8)
project(OpenGL)
set(CMAKE_CXX_COMPILER "clang++")

find_package(OpenGL REQUIRED) # GLU
set(LIBS ${OPENGL_LIBRARY})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(tutorial)
add_subdirectory(glx)
