
cmake_minimum_required(VERSION 3.3...4.3)
set(CMAKE_CXX_STANDARD 20)

#Add PerlinNoise to the subdirectories list, make a library as there isn't an existing CML in that directory

project (PerlinNoiseLib)
add_Library(PerlinNoiseLib INTERFACE)
target_include_directories(PerlinNoiseLib INTERFACE PerlinNoise.)


#We just need to add subdirectory for these libraries, however...
add_subdirectory(glfw)
add_subdirectory(imgui)