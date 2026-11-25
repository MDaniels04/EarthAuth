#As with our other CMAKELists, we want to enable shit in the src and includes folders to be included as needed.
#Additionally, the main.cpp - the application - should be able to include stuff from our include folder if wanted


set(AppHeaders "${PROJECT_SOURCE_DIR}/include/")
file(GLOB_RECURSE AppSources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

#Create the library that we will use in the application program, especially
add_library(AppLib ${AppHeaders} ${AppSources})

target_include_directories(AppLib PUBLIC include/)
target_link_libraries(AppLib EarthAuthLib)
add_executable(EarthAuthDemo main.cpp ${AppSources} ${AppHeaders})


target_compile_features(EarthAuthDemo PRIVATE cxx_std_20) #Enforce C++ std 20 here too...
target_link_libraries(EarthAuthDemo PRIVATE  AppLib)