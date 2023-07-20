#include "ImGuiLayer.hpp"

#include "Atakama/Core/Window.hpp"
#include "Atakama/Core/FileSystem.hpp"
#include "Atakama/Engine/RenderSystem.hpp"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <ImGuizmo.h>

#include <GLFW/glfw3.h>

namespace Atakama
{

ImGuiLayer::ImGuiLayer(Ref<RenderSystem>& renderSystem, Ref<Window>& window)
: Layer("ImGui Layer"), m_RenderSystem(renderSystem), m_Window(window)
{

}

void ImGuiLayer::OnAttach()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Disable loading/saving any ini file
    io.IniFilename = NULL;
 
    if (IsEditor())
    {
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        // It enables detaching ImGui window from the main window
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    }

    ImGui::StyleColorsDark();
    
    SetCustomTheme();

    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

}
void ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
}

void ImGuiLayer::End()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO &io = ImGui::GetIO();
    uint32_t frameBufferWidth = m_Window->GetFrameBufferWidth();
    uint32_t frameBufferHeight = m_Window->GetFrameBufferHeight();
    m_RenderSystem->SetViewport(0, 0, frameBufferWidth, frameBufferHeight);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void ImGuiLayer::SetCustomTheme()
{
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.22f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.22f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.22f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.47f, 0.49f, 0.54f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.47f, 0.50f, 0.54f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.22f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.22f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
}


}
