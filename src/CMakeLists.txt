set(PROGRAMS main)
# TODO: change this when the programs get installed, make it platform indep.
add_definitions(-DSHADERS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shaders/")
FILE(GLOB SOURCES *.cpp)
FILE(GLOB HEADERS *.h)

foreach(program ${PROGRAMS})
    add_executable(${program} ${SOURCES} ${HEADERS})
    target_link_libraries(${program} ${CORELIBS})
endforeach(program)
