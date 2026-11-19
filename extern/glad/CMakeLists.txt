#TODO Revisit this
#Workaround CMAKELists to get GLAD up and running


cmake_minimum_required(VERSION 3.3...4.3)
project(glad)

add_library(glad)   #TODO Vulkan file is here but not currently being built with cmake
target_sources(glad PRIVATE "src/gl.c")
target_include_directories(glad PUBLIC "include/")