project(Editor
    LANGUAGES
    C
    CXX
)

# find_package(OpenGL REQUIRED)
# find_package(Vulkan REQUIRED)
# find_package(GLEW REQUIRED)

add_executable(${PROJECT_NAME})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

set(SOURCE_ROOT ${PROJECT_SOURCE_DIR}/src)

set(LIBS_PATH ${PROJECT_SOURCE_DIR}/libs)

file(GLOB_RECURSE HEADERS ${SOURCE_ROOT}/*.hpp)
file(GLOB_RECURSE SOURCES ${SOURCE_ROOT}/*.cpp)

source_group_by_folder(HEADERS ${HEADERS} SOURCES ${SOURCES})

set(SHADER_ROOT ${SOURCE_ROOT}/shaders)
file(GLOB_RECURSE SHADERS
    ${SHADER_ROOT}/*.vert
    ${SHADER_ROOT}/*.frag
)

# target_add_shaders(${PROJECT_NAME}
#     PRIVATE
#         ${SHADERS}
# )

set(SHADERS_ROOT ${PROJECT_SOURCE_DIR}/src/shaders)

target_add_assets(${PROJECT_NAME} "shaders"
    ${SHADERS}
)

set(ASSETS_ROOT ${PROJECT_SOURCE_DIR}/../assets)

set(TEXTURES_ROOT ${ASSETS_ROOT}/textures)
file(GLOB_RECURSE TEXTURES
    ${TEXTURES_ROOT}/*.*
)

target_add_assets(${PROJECT_NAME} "assets/textures"
    ${TEXTURES}
)


set(MODELS_ROOT ${ASSETS_ROOT}/models)
file(GLOB_RECURSE MODELS
    ${MODELS_ROOT}/*.*
)

target_add_assets(${PROJECT_NAME} "assets/models"
    ${MODELS}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${SOURCE_ROOT}
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${HEADERS} ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        # ${OPENGL_gl_LIBRARY}
        # glfw
        # GLEW::GLEW
        glm::glm
        # stb
        # Vulkan::Vulkan
        imgui
        spdlog
        # # tinyobjloader
        EnTT
        Engine
)

target_precompile_headers(${PROJECT_NAME}
    PUBLIC
        ${SOURCE_ROOT}/pch.hpp
)


# add_subdirectory("libs/tinyobjloader")
