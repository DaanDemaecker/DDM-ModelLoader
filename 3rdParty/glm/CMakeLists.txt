include(FetchContent)

if (NOT TARGET glm::glm)

    set(GLM_ENABLE_CXX_17 ON CACHE BOOL "" FORCE)
    set(GLM_ENABLE_TESTS OFF CACHE BOOL "" FORCE)
    set(GLM_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
    set(GLM_ENABLE_FAST_MATH OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e # 1.0.1
        GIT_SHALLOW TRUE
    )

    FetchContent_MakeAvailable(glm)

endif()

target_link_libraries(${LIBRARY_NAME}
    PUBLIC
        glm::glm
)
