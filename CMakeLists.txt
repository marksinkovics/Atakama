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

if (MSVC)
    message(STATUS "Apply compile options: /Od /ZI")
    add_compile_options(
        $<$<CONFIG:DEBUG>:/Od>
        $<$<CONFIG:DEBUG>:/ZI>
    )
endif()

add_subdirectory("vendor")
add_subdirectory("Engine")
add_subdirectory("Sandbox")
add_subdirectory("Editor")

if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "Editor")
endif()