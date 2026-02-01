add_library(FBXSDK SHARED IMPORTED GLOBAL)

set_target_properties(FBXSDK PROPERTIES
    IMPORTED_LOCATION
        "${CMAKE_CURRENT_SOURCE_DIR}/dll/release/libfbxsdk.dll"
    IMPORTED_IMPLIB
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/release/libfbxsdk.lib"
    INTERFACE_INCLUDE_DIRECTORIES
        "${CMAKE_CURRENT_SOURCE_DIR}/include"

    IMPORTED_LOCATION_DEBUG
        "${CMAKE_CURRENT_SOURCE_DIR}/dll/debug/libfbxsdk.dll"
    IMPORTED_IMPLIB_DEBUG
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/debug/libfbxsdk.lib"
)