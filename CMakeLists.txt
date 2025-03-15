cmake_minimum_required(VERSION 3.10)

# Set the project name
project(DDMModelLoader VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create a STATIC library
add_library(DDMModelLoader STATIC src/DDMModelLoader.cpp)

# Ensure headers are available for consumers
target_include_directories(DDMModelLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

