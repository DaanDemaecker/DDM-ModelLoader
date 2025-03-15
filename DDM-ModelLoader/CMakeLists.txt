cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(DDMModelLoader VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Specify the path to your source files
add_library(DDMModelLoader
    src/DDMModelLoader.cpp
)

# Specify any public headers (optional)
target_include_directories(DDMModelLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
