set(PROGRAM glx)
FILE(GLOB SOURCES *.cpp)
FILE(GLOB HEADERS *.h)

find_package(X11 REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
set(LIBS ${LIBS} ${GLEW_LIBRARY} ${X11_LIBRARY})

add_executable(${PROGRAM} ${COMMON_SOURCES} ${SOURCES} ${HEADERS})
target_link_libraries(${PROGRAM} ${LIBS})
