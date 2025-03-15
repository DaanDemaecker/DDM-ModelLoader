cmake_minimum_required(VERSION 3.10)

# Set the project name
project(DDMModelLoader VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create a STATIC library
add_library(DDMModelLoader STATIC src/DDMModelLoader.cpp)

# Ensure headers are available for consumers
target_include_directories(DDMModelLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Force the library to be built in the same directory as TestSolution.exe
set_target_properties(DDMModelLoader PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
