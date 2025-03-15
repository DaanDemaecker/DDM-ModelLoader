cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(DDMModelLoader VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Specify the path to your source files
add_library(DDMModelLoader STATIC src/DDMModelLoader.cpp)

# Specify the include directories for the target
target_include_directories(DDMModelLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Optionally, set properties for the output directory if you want more control
# set_target_properties(DDMModelLoader PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# This ensures that the library is easily found by the `TestSolution` project
export(TARGETS DDMModelLoader FILE "${CMAKE_BINARY_DIR}/DDMModelLoaderConfig.cmake")

# You can also install the target if needed, but it’s optional for this use case
# install(TARGETS DDMModelLoader EXPORT DDMModelLoaderConfig)
