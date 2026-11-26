

cmake_minimum_required(VERSION 3.3...4.3)
set(CMAKE_CXX_STANDARD 20)

#Add PerlinNoise to the subdirectories list, make a library as there isn't an existing CML in that directory

project (PerlinNoiseLib)
add_Library(PerlinNoiseLib INTERFACE)
target_include_directories(PerlinNoiseLib INTERFACE PerlinNoise.)


#TODO this is a working soloution, might be better to find packages and link those rather than just subidercting

#We just need to add subdirectory for these libraries, however...
add_subdirectory(glfw)
#add_subdirectory(imgui) imgui DOESNT have a cmake lists??

#glad works in tandem with glfw to help load open GL (Or Vulkan)
add_subdirectory(glad)

add_subdirectory(glm) #gl maths

#Add the subdirectory for the cmake build of ImGUI
#add_subdirectory(cmake-imgui-master)