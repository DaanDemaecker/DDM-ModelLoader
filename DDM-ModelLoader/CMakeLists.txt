cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(DDMModelLoader VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Specify the path to your source files
add_library(DDMModelLoader STATIC src/DDMModelLoader.cpp)

# Specify the include directories for the target
target_include_directories(DDMModelLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Optionally, specify output directories for the library (static library)
set_target_properties(DDMModelLoader PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Export the target for use with FetchContent
export(TARGETS DDMModelLoader FILE "${CMAKE_BINARY_DIR}/DDMModelLoaderConfig.cmake")
