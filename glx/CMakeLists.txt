set(PROGRAMS glx)
FILE(GLOB SOURCES *.cpp)
FILE(GLOB HEADERS *.h)

foreach(program ${PROGRAMS})
    add_executable(${program} ${SOURCES} ${HEADERS})
    target_link_libraries(${program} ${CORELIBS} -lX11)
endforeach(program)
