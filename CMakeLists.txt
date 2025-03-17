cmake_minimum_required(VERSION 3.11)
project(DDMModelLoader VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_policy(SET CMP0079 NEW)

set(EXECUTABLE_NAME DDMModelLoader)

add_library(${EXECUTABLE_NAME} STATIC src/DDMModelLoader.cpp  "src/ObjLoader.h" "src/ObjLoader.cpp" "src/Vertex.h" "src/FbxLoader.h" "src/FbxLoader.cpp")

target_include_directories(DDMModelLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(3rdParty)

