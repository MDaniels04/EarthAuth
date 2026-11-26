#https://hsf-training.github.io/hsf-training-cmake-webpage/06-projectstructure/index.html


cmake_minimum_required(VERSION 3.3...4.3)
set(CMAKE_CXX_STANDARD 20)

#CMAKE lists for the source directory, we want to ensure that all of our source files can access the necessary headers...
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/EarthAuth/") #IMPORTANT THIS IS THE ROOT SRC DIR
                #Is project source dir ok to use here?

#Define the directory for all our shaders so we can access them in the  build...
#set(SHADERS "${PROJECT_SOURCE_DIR}/resources/shaders/")

file(GLOB_RECURSE EarthAuthLibSources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

#Define the library that will be used in our application
add_library(EarthAuthLib STATIC  ${EarthAuthLibSources} ${HEADER_LIST})

target_compile_features(EarthAuthLib PUBLIC cxx_std_20)

set_target_properties(EarthAuthLib PROPERTIES LINKER_LANGUAGE CXX) #Idiot proof, explicitly tell the linker "C++!"

#In the blog used as a framework, they use this on top of the definition earlier...
target_include_directories(EarthAuthLib PUBLIC ../include)

#setup our pch to actually pc
target_precompile_headers(EarthAuthLib PRIVATE "${PROJECT_SOURCE_DIR}/include/pch.h")

target_link_libraries(EarthAuthLib PUBLIC
        glad
        glfw
        glm)


#This is to allow us to use the graphical debugging tool, renderdoc
target_include_directories(EarthAuthLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/extern/renderdoc)

#visual studio organising helper
source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER_LIST}
)