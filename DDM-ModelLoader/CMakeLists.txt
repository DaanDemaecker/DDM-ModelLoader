cmake_minimum_required(VERSION 3.10)

# Set the project name
project(DDMModelLoader VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the library
add_library(DDMModelLoader STATIC
    src/DDMModelLoader.cpp
)

# Ensure headers are available for consumers
target_include_directories(DDMModelLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Install the library (optional)
install(TARGETS DDMModelLoader DESTINATION lib)
install(DIRECTORY src/ DESTINATION include FILES_MATCHING PATTERN "*.h")
