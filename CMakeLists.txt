cmake_minimum_required(VERSION 3.3...4.3) #Fun fact: CMAKE 3.3 came out in 2015 - and this is the version on the uni PCS :')
project(EarthAuth
        DESCRIPTION "Honours Project"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

#Adds our external libraries stuff...

add_subdirectory(apps)
add_subdirectory(extern)