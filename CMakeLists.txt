cmake_minimum_required(VERSION 3.24.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

project(OpenGLSample
    LANGUAGES
    C
    CXX
)

include("cmake/add_asset.cmake")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_executable(app)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(app PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED OFF
    CXX_EXTENSIONS OFF
)

set(SOURCE_ROOT ${PROJECT_SOURCE_DIR}/src)
set(LIBS_PATH ${PROJECT_SOURCE_DIR}/libs)

file(GLOB_RECURSE HEADERS ${SOURCE_ROOT}/*.hpp)
file(GLOB_RECURSE SOURCES ${SOURCE_ROOT}/*.cpp)

set(SHADER_ROOT ${SOURCE_ROOT}/shaders)
file(GLOB_RECURSE SHADERS
    ${SHADER_ROOT}/*.vert
    ${SHADER_ROOT}/*.frag
)

# target_add_shaders(app
#     PRIVATE
#         ${SHADERS}
# )

set(SHADERS_ROOT ${PROJECT_SOURCE_DIR}/src/shaders)

target_add_assets(app shaders
${SHADERS}
)

set(ASSETS_ROOT ${PROJECT_SOURCE_DIR}/assets)
set(TEXTURES_ROOT ${ASSETS_ROOT}/textures)
file(GLOB_RECURSE TEXTURES
    ${TEXTURES_ROOT}/*.*
)
target_add_assets(app "assets/textures"
    ${TEXTURES}
)

target_include_directories(app
    PUBLIC
        ${SOURCE_ROOT}
)

target_sources(app
    PRIVATE
        ${HEADERS} ${SOURCES}
)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

target_link_libraries(app
    PRIVATE
        ${OPENGL_gl_LIBRARY}
        glfw
        GLEW::GLEW
        glm::glm
        # tinyobjloader
)

target_precompile_headers(app
    PUBLIC
        ${SOURCE_ROOT}/Utils/Utils.hpp
)

# add_subdirectory("libs/tinyobjloader")
