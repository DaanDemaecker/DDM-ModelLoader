cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(DDMModelLoader VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Specify the path to your source files
add_library(DDMModelLoader STATIC src/DDMModelLoader.cpp)

# Specify the include directories for the target
target_include_directories(DDMModelLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Specify the output directories for the static library
set_target_properties(DDMModelLoader PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/build/x64-Debug/lib
)

# Export the target and make it available for FetchContent
export(TARGETS DDMModelLoader FILE "${CMAKE_BINARY_DIR}/DDMModelLoaderConfig.cmake")
