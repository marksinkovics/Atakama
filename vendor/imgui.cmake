find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)

set(imgui_SOURCE_DIR_ ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

file(GLOB imgui_sources CONFIGURE_DEPENDS  "${imgui_SOURCE_DIR_}/*.cpp")
file(GLOB imgui_impl CONFIGURE_DEPENDS
    ${imgui_SOURCE_DIR_}/backends/imgui_impl_opengl3_loader.h
    ${imgui_SOURCE_DIR_}/backends/imgui_impl_opengl3.h
    ${imgui_SOURCE_DIR_}/backends/imgui_impl_opengl3.cpp
    ${imgui_SOURCE_DIR_}/backends/imgui_impl_glfw.h
    ${imgui_SOURCE_DIR_}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR_}/backends/imgui_impl_vulkan.cpp
    ${imgui_SOURCE_DIR_}/backends/imgui_impl_vulkan.h
)

add_library(imgui STATIC ${imgui_sources} ${imgui_impl})

set_target_properties(imgui
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED OFF
        CXX_EXTENSIONS OFF
)

target_include_directories(imgui
    PUBLIC
        $<BUILD_INTERFACE:${imgui_SOURCE_DIR_}>
        $<BUILD_INTERFACE:${imgui_SOURCE_DIR_}>/backends
)


target_link_libraries(imgui
    PUBLIC
        glfw
        ${OPENGL_LIBRARIES}
        Vulkan::Vulkan
)