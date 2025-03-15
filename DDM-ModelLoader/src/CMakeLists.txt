# Set the version and project name
set(DDMModelLoader_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create the static library
add_library(DDMModelLoader STATIC DDMModelLoader.cpp)

# Specify the include directory for this library (important!)
target_include_directories(DDMModelLoader PUBLIC ${DDMModelLoader_INCLUDE_DIR})

# Optionally, install the library (e.g., to a system path or for packaging)
install(TARGETS DDMModelLoader
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

# Install the headers for distribution (in case you use "install")
install(DIRECTORY ${DDMModelLoader_INCLUDE_DIR}/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
