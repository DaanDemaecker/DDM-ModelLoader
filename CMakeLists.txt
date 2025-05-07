cmake_minimum_required(VERSION 3.11)
project(DDMModelLoader VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_policy(SET CMP0079 NEW)

set(EXECUTABLE_NAME DDMModelLoader)

set(INC_FILES 
	"DDMModelLoader/Mesh"
	"DDMModelLoader/ObjLoader.h"
	"DDMModelLoader/Vertex.h"
	"DDMModelLoader/FbxLoader.h"
	"DDMModelLoader/GltfLoader.h" 
)

set(SOURCE_FILES 
	"DDMModelLoader/DDMModelLoader.cpp"
	"DDMModelLoader/ObjLoader.cpp"
	"DDMModelLoader/FbxLoader.cpp" 
	"DDMModelLoader/GltfLoader.cpp"
 )

add_library(${EXECUTABLE_NAME} STATIC ${SOURCE_FILES} ${INC_FILES})

target_include_directories(DDMModelLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(3rdParty)

