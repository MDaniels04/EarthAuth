cmake_minimum_required(VERSION 4.3)
project(EarthAuth
        DESCRIPTION "Honours Project"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

#Adds our external libraries stuff...

add_subdirectory(apps)
add_subdirectory(extern)