set(PROGRAM volumetric_rendering)
# TODO: change this when the programs get installed, make it platform indep.
add_definitions(-DSHADERS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shaders/")
FILE(GLOB SOURCES *.cpp)
FILE(GLOB HEADERS *.h)

find_package(OpenGL REQUIRED) # GLU
find_package(GLEW REQUIRED)
INCLUDE(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
set(LIBS ${LIBS} ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES})

add_executable(${PROGRAM} ${COMMON_SOURCES} ${SOURCES} ${HEADERS})
target_link_libraries(${PROGRAM} ${LIBS})
