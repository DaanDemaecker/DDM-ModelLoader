cmake_minimum_required(VERSION 4.1)
project(DDMModelLoader VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_policy(SET CMP0079 NEW)

set(LIBRARY_NAME DDMModelLoader)

#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")

set(INC_FILES 
	"DDMModelLoader/ModelLoader.h"
	"DDMModelLoader/DDMModelLoader.h"

	"DDMModelLoader/Mesh.h"
	"DDMModelLoader/Vertex.h"
	
	"DDMModelLoader/Includes/GLMIncludes.h"
	
	"DDMModelLoader/Export.h"
	) 

set(SOURCE_FILES 
	"DDMModelLoader/ModelLoader.cpp"

	"DDMModelLoader/DDMModelLoader.cpp")

add_library(${LIBRARY_NAME} SHARED ${SOURCE_FILES} ${INC_FILES})

target_include_directories(DDMModelLoader
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_compile_definitions(DDMModelLoader
    PRIVATE DDMMODELLOADER_BUILD
)

add_subdirectory(3rdparty)