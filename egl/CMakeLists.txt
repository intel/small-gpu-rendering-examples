set(PROGRAM egl)
FILE(GLOB SOURCES *.cpp)
FILE(GLOB HEADERS *.h)

include (FindPkgConfig)

find_package(OpenGL REQUIRED) # GLU
pkg_check_modules (EGL egl)
pkg_check_modules (GLESV2 glesv2)
include_directories(
    ${EGL_INCLUDE_DIRS}
    ${GLESV2_INCLUDE_DIRS}
)
set(LIBS ${LIBS} ${EGL_LIBRARIES} ${GLESV2_LIBRARIES})

add_executable(${PROGRAM} ${SOURCES} ${HEADERS})
target_link_libraries(${PROGRAM} ${LIBS})
