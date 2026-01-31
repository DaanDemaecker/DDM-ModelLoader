
target_link_libraries(${LIBRARY_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/debug/libfbxsdk.lib)

target_compile_definitions(${LIBRARY_NAME} PRIVATE FBXSDK_SHARED)

# Include FBX SDK headers
target_include_directories(${LIBRARY_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link FBX SDK libraries
target_link_libraries(${LIBRARY_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/debug/libfbxsdk.lib)


# Optional: Specify properties for MSVC runtime library linkage
if (MSVC)
    set_property(TARGET ${LIBRARY_NAME} PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()


set(FBX_SDK_DLL
    ${CMAKE_CURRENT_SOURCE_DIR}/dll/debug/libfbxsdk.dll
)

set_property(TARGET DDMModelLoader
    PROPERTY
        INTERFACE_RUNTIME_DEPENDENCIES
            ${FBX_SDK_DLL}
)