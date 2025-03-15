cmake_minimum_required(VERSION 3.10)
project(DDMModelLoader VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(DDMModelLoader STATIC src/DDMModelLoader.cpp )

target_include_directories(DDMModelLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)



include(FetchContent)

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
	GIT_SHALLOW true
)

FetchContent_MakeAvailable(glm)


target_link_libraries(DDMModelLoader PRIVATE glm::glm)