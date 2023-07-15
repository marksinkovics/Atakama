#include "ProjectSettingsLayer.hpp"

#include "EditorApplication.hpp"


#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

namespace Atakama::Editor
{

    ProjectSettingsLayer::ProjectSettingsLayer(const EditorUIConfig& config)
        : Layer("Project Settings Layer"), m_UIConfig(config)
    {
        m_Application = (EditorApplication*)g_RuntimeGlobalContext.m_Application;
    }

    void ProjectSettingsLayer::OnAttach()
    {

    }

    void ProjectSettingsLayer::OnDetach()
    {

    }

    void ProjectSettingsLayer::OnUpdateUI(float ts)
    {
        ImGui::SetNextWindowClass(&m_UIConfig.editorTopLevelClass);
        ImGui::Begin("Project Settings");
        ImGui::DockSpace(m_UIConfig.projectSettingsDockSpace, ImVec2(0, 0), 0, &m_UIConfig.projectSettingsClass);
        ImGui::End();
    }

}
