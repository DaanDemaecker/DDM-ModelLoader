cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(DDMModelLoader VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Specify the path to your source files
add_library(DDMModelLoader STATIC src/DDMModelLoader.cpp)

# Specify the include directories for the target (use the path relative to the CMake binary directory)
target_include_directories(DDMModelLoader PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

# Specify the output directory for static libraries
set_target_properties(DDMModelLoader PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/build/x64-Debug/lib
)

# Export the target configuration so TestSolution can find it
install(TARGETS DDMModelLoader EXPORT DDMModelLoaderConfig)
install(EXPORT DDMModelLoaderConfig DESTINATION "${CMAKE_BINARY_DIR}/cmake/DDMModelLoader")
