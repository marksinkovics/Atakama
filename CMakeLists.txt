cmake_minimum_required(VERSION 3.24.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

project(Atakama
    LANGUAGES
    C
    CXX
)

include("cmake/add_asset.cmake")
include("cmake/source_group_by_folder.cmake")

add_subdirectory("vendor")
add_subdirectory("Engine")
add_subdirectory("Sandbox")
add_subdirectory("Editor")

if(CMAKE_GENERATOR MATCHES "Visual Studio")
    SET(CMAKE_DEFAULT_STARTUP_PROJECT "Editor")
endif()