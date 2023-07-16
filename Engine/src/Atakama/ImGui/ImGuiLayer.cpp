#include "ImGuiLayer.hpp"

#include "Atakama/Core/Window.hpp"
#include "Atakama/Core/FileSystem.hpp"
#include "Atakama/Engine/RenderSystem.hpp"

#include <imgui.h>
#include <imgui_internal.h>
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

    io.IniFilename = NULL;
    //ImGui::LoadIniSettingsFromDisk(FileSystem::GetImGuiInitPath().string().c_str());

    if (IsEditor())
    {
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        // It enables detaching ImGui window from the main window
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    }

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

}
void ImGuiLayer::OnDetach()
{
    ImGui::SaveIniSettingsToDisk(FileSystem::GetImGuiInitPath().string().c_str());

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


}
