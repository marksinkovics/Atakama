set(imguizmo_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ImGuizmo)

file(GLOB imguizmo_sources CONFIGURE_DEPENDS "${imguizmo_SOURCE_DIR}/*.cpp")
file(GLOB imguizmo_headers CONFIGURE_DEPENDS "${imguizmo_SOURCE_DIR}/*.h")

add_library(ImGuizmo STATIC ${imguizmo_sources} ${imguizmo_headers})

set_target_properties(ImGuizmo
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED OFF
        CXX_EXTENSIONS OFF
)

target_include_directories(ImGuizmo
    PUBLIC
        $<BUILD_INTERFACE:${imguizmo_SOURCE_DIR}>
)

target_link_libraries(ImGuizmo
    PUBLIC
        imgui
)