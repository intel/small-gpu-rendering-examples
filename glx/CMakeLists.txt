set(PROGRAMS glx)
FILE(GLOB SOURCES *.cpp)
FILE(GLOB HEADERS *.h)

find_package(X11 REQUIRED)
set(LIBS ${LIBS} ${X11_LIBRARY})

foreach(program ${PROGRAMS})
    add_executable(${program} ${SOURCES} ${HEADERS})
    target_link_libraries(${program} ${LIBS})
endforeach(program)
