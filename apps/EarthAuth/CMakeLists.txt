
add_executable(EarthAuthDemo main.cpp)
target_compile_features(EarthAuthDemo PRIVATE cxx_std_20) #Enforce C++ std 20 here too...
target_link_libraries(EarthAuthDemo PRIVATE EarthAuthLib PerlinNoiseLib)