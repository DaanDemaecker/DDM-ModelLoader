include(FetchContent)

#include glm
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
	GIT_SHALLOW true
)

FetchContent_MakeAvailable(glm)

target_link_libraries(${EXECUTABLE_NAME} PUBLIC glm::glm)