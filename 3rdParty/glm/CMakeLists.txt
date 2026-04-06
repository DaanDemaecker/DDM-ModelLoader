include(FetchContent)

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	1.0.3 #refs/tags/1.0.1
	GIT_SHALLOW true
)

FetchContent_MakeAvailable(glm)

target_include_directories(${LIBRARY_NAME}
    PUBLIC
        ${glm_SOURCE_DIR}
)
