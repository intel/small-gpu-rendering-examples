set(PROGRAM glx)
FILE(GLOB SOURCES *.cpp)
FILE(GLOB HEADERS *.h)

find_package(X11 REQUIRED)
set(LIBS ${LIBS} ${X11_LIBRARY})

add_executable(${PROGRAM} ${SOURCES} ${HEADERS})
target_link_libraries(${PROGRAM} ${LIBS})
