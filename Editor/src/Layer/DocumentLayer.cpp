#include "DocumentLayer.hpp"

#include "EditorApplication.hpp"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

namespace Atakama::Editor
{

DocumentLayer::DocumentLayer()
    : Layer("Document Layer"), m_UIConfig(GetUIConfig())
{
    m_Application = (EditorApplication*)g_RuntimeGlobalContext.m_Application;
}

void DocumentLayer::OnAttach()
{

}

void DocumentLayer::OnDetach()
{

}

void DocumentLayer::OnUpdateUI(float ts)
{
    ImGui::SetNextWindowClass(&m_UIConfig.editorTopLevelClass);
    ImGui::Begin(GetImGuiWindowId(WindowId::Document).c_str());
    ImGui::BeginChild("statusbar", ImVec2(ImGui::GetContentRegionAvail().x, toolbarSize));
    ImGui::Text("[STATUS BAR]"); ImGui::SameLine(); ImGui::Button("Toolbar goes here", ImVec2(0, toolbarSize));
    ImGui::EndChild();
    ImGui::DockSpace(m_UIConfig.documentDockSpace, ImVec2(0, 0), 0, &m_UIConfig.documentClass);
    ImGui::End();
}

}
