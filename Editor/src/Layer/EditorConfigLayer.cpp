#include "EditorConfigLayer.hpp"

#include "EditorApplication.hpp"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

namespace Atakama::Editor
{

    EditorConfigLayer::EditorConfigLayer(EditorUIConfig& config)
        : Layer("Editor Config Layer"), m_UIConfig(config)
    {
        m_Application = (EditorApplication*)g_RuntimeGlobalContext.m_Application;
    }

    void EditorConfigLayer::OnAttach()
    {

    }

    void EditorConfigLayer::OnDetach()
    {

    }

    void EditorConfigLayer::OnUpdateUI(float ts)
    {
        static bool first_time = true;
        if (first_time) {
            first_time = false;

            ImGuiViewport* viewport = ImGui::GetMainViewport();

            ImVec2 workSize = ImGui::GetMainViewport()->WorkSize;
            ImVec2 workPos = ImGui::GetMainViewport()->WorkPos;
            ImGui::DockBuilderRemoveNode(m_UIConfig.editorTopLevelDockSpace); // Clear out existing layout
            ImGui::DockBuilderAddNode(m_UIConfig.editorTopLevelDockSpace, ImGuiDockNodeFlags_None); // Add empty node
            ImGui::DockBuilderSetNodeSize(m_UIConfig.editorTopLevelDockSpace, workSize);
            ImGui::DockBuilderSetNodePos(m_UIConfig.editorTopLevelDockSpace, workPos);

            ImGui::DockBuilderDockWindow("Document - asdfasdf###Document", m_UIConfig.editorTopLevelDockSpace);
            ImGui::DockBuilderDockWindow("Project Settings", m_UIConfig.editorTopLevelDockSpace);

            ImGui::DockBuilderFinish(m_UIConfig.editorTopLevelDockSpace);

            Config();
        }

    }

    void EditorConfigLayer::Config()
    {
        {
            ImGui::DockBuilderSetNodeSize(m_UIConfig.documentDockSpace, ImGui::GetMainViewport()->WorkSize);
            ImGui::DockBuilderDockWindow("Viewport", m_UIConfig.documentDockSpace);
            ImGui::DockBuilderDockWindow("Depth", m_UIConfig.documentDockSpace);

            ImGuiID documentLeft = ImGui::DockBuilderSplitNode(m_UIConfig.documentDockSpace, ImGuiDir_Left, 0.25f, nullptr, &m_UIConfig.documentDockSpace);
            ImGuiID documentDown = ImGui::DockBuilderSplitNode(m_UIConfig.documentDockSpace, ImGuiDir_Down, 0.2f, nullptr, &m_UIConfig.documentDockSpace);
            ImGuiID componentsBottom = ImGui::DockBuilderSplitNode(documentLeft, ImGuiDir_Down, 0.25f, nullptr, &documentLeft);
            ImGui::DockBuilderDockWindow("Scene View", documentLeft);
            ImGui::DockBuilderDockWindow("Stats", documentDown);
            ImGui::DockBuilderDockWindow("Object Properties", componentsBottom);
            ImGui::DockBuilderFinish(m_UIConfig.documentDockSpace);
        }

        {
            ImGui::DockBuilderSetNodeSize(m_UIConfig.projectSettingsDockSpace, ImGui::GetMainViewport()->WorkSize);
            ImGuiID projectSettingsRight = ImGui::DockBuilderSplitNode(m_UIConfig.projectSettingsDockSpace, ImGuiDir_Down, 0.5f, nullptr, &m_UIConfig.projectSettingsDockSpace);
            ImGui::DockBuilderDockWindow("Categories", projectSettingsRight);
            ImGui::DockBuilderFinish(m_UIConfig.projectSettingsDockSpace);
        }
    }

}
