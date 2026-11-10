
#Do we need to define a library like this?
cmake_minimum_required(VERSION 4.3)

set(CMAKE_CXX_STANDARD 20)

#Add PerlinNoise to the subdirectories list, make a library

project (PerlinNoiseLib)
add_Library(PerlinNoiseLib INTERFACE)
target_include_directories(PerlinNoiseLib INTERFACE PerlinNoise.)