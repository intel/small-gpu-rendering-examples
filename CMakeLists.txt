cmake_minimum_required(VERSION 2.8)
project(OpenGL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)

FILE(GLOB COMMON_SOURCES common/*.cpp common/*.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(tutorial)
add_subdirectory(glx)
add_subdirectory(egl)
