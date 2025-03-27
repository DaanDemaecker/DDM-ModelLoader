include(FetchContent)


#include tinygltf
FetchContent_Declare(
	tinygltf
	GIT_REPOSITORY https://github.com/syoyo/tinygltf
	GIT_TAG v2.9.5
    GIT_SHALLOW true
)

# Make the fetched content available
FetchContent_MakeAvailable(tinygltf)

# Link libraries
target_link_libraries(${EXECUTABLE_NAME} PUBLIC tinygltf)