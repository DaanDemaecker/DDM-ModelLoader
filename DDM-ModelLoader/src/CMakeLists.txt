# Set the version and project name
set(DDMModelLoader_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Add the include directory
include_directories(${DDMModelLoader_INCLUDE_DIR})

# Add the library target
add_library(DDMModelLoader STATIC DDMModelLoader.cpp)

# Specify the install locations
target_include_directories(DDMModelLoader PUBLIC ${DDMModelLoader_INCLUDE_DIR})

# Optionally, install the library (e.g., to a system path or for packaging)
install(TARGETS DDMModelLoader
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

install(DIRECTORY ${DDMModelLoader_INCLUDE_DIR}/DDMModelLoader
    DESTINATION include
)