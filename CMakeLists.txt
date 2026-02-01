cmake_minimum_required(VERSION 3.1)
project(DDMModelLoader VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_policy(SET CMP0079 NEW)

set(LIBRARY_NAME DDMModelLoader)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")

set(INC_FILES 
	"DDMModelLoader/ModelLoaders/ModelLoader.h"
	"DDMModelLoader/ModelLoaders/ObjLoader.h"
	"DDMModelLoader/ModelLoaders/GltfLoader.h" 
	"DDMModelLoader/ModelLoaders/FbxLoader.h"

	"DDMModelLoader/DDMModelLoader.h"
	"DDMModelLoader/Mesh"
	"DDMModelLoader/Vertex.h"
	"DDMModelLoader/Includes/GLMIncludes.h" "DDMModelLoader/Export.h") 

set(SOURCE_FILES 
	"DDMModelLoader/ModelLoaders/ModelLoader.cpp"
	"DDMModelLoader/ModelLoaders/ObjLoader.cpp"
	"DDMModelLoader/ModelLoaders/GltfLoader.cpp"
	"DDMModelLoader/ModelLoaders/FbxLoader.cpp" 

	"DDMModelLoader/DDMModelLoader.cpp"
 )

add_library(${LIBRARY_NAME} SHARED ${SOURCE_FILES} ${INC_FILES})

target_include_directories(DDMModelLoader
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_compile_definitions(DDMModelLoader
    PRIVATE DDMMODELLOADER_BUILD
)

add_subdirectory(3rdparty)

add_custom_command(
    TARGET DDMModelLoader
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:FBXSDK>
        $<TARGET_FILE_DIR:${LIBRARY_NAME}>
)

target_link_libraries(${LIBRARY_NAME} PUBLIC FBXSDK)