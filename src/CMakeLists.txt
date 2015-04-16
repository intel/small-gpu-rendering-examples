set(PROGRAMS main)
# TODO: change this when the programs get installed, make it platform indep.
add_definitions(-DSHADERS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shaders/")

foreach(program ${PROGRAMS})
    add_executable(${program} ${program}.cpp)
    target_link_libraries(${program} ${CORELIBS})
endforeach(program)
