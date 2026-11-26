#https://hsf-training.github.io/hsf-training-cmake-webpage/06-projectstructure/index.html

cmake_minimum_required(VERSION 3.3...4.3) #Fun fact: CMAKE 3.3 came out in 2015 - and this is the version on the uni PCS :')

project(EarthAuth
        VERSION 0.01
        DESCRIPTION "Honours Project"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>") #These lines come highly reccomended by LowLevelGameDev;
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>") #/

#IF this is the main page and not being included as a library
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    #This line allows folder suppourt in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    #Docs suppourt - we only want to build docs if doxygen has been found
    find_package(Doxygen)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else ()
        message(WARNING "'Doxygen' was not found")
    endif()


    #find_package(ImGui DIR ")

#Endif main page
endif()

    #subdirectories to always include, CMAKELists in each one respectively will take care of each other

    #src files for the "engine" code
add_subdirectory(src)
    #apps
add_subdirectory(apps)

    #external
add_subdirectory(extern)

