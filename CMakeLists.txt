cmake_minimum_required(VERSION 3.10)
project(DDMModelLoader VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(DDMModelLoader STATIC src/DDMModelLoader.cpp)

target_include_directories(DDMModelLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Allow FetchContent to make this available
add_subdirectory(.)
