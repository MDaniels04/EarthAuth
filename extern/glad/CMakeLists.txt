#Code from:
#https://github.com/Dav1dde/glad/wiki/C

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
file(GLOB BUTTERFLIES_SOURCES_C ${CMAKE_CURRENT_SOURCE_DIR} *.c glad/src/gl.c)