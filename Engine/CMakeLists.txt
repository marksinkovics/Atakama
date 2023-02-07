project(Engine
    LANGUAGES
    C
    CXX
)

find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)
find_package(GLEW REQUIRED)

set(SOURCE_ROOT ${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE HEADERS ${SOURCE_ROOT}/*.hpp)
file(GLOB_RECURSE SOURCES ${SOURCE_ROOT}/*.cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" FILES ${HEADERS} ${SOURCES})

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${OPENGL_gl_LIBRARY}
        glfw
        GLEW::GLEW
        glm::glm
        stb
        Vulkan::Vulkan
        imgui
        spdlog
        # tinyobjloader
        EnTT
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${SOURCE_ROOT}
        EnTT
    PRIVATE
        ${SOURCE_ROOT}
)

target_precompile_headers(${PROJECT_NAME}
    PUBLIC
        ${SOURCE_ROOT}/pch.hpp
)