#include "EditorLayer.hpp"

#include "EditorApplication.hpp"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

namespace Atakama::Editor
{

    EditorLayer::EditorLayer()
        : Layer("Editor Layer")
    {
    }

    void EditorLayer::OnAttach()
    {

    }

    void EditorLayer::OnDetach()
    {

    }

    void EditorLayer::OnUpdateUI(float ts)
    {
        // Generate IDs
        {

            m_UIConfig.editorTopLevelClass.ClassId = ImGui::GetID("MyTopLevelClass");
            m_UIConfig.editorTopLevelClass.DockingAllowUnclassed = false;
            m_UIConfig.editorTopLevelClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoDockingSplitOther | ImGuiDockNodeFlags_NoDockingSplitMe;

            m_UIConfig.documentClass.ClassId = ImGui::GetID("DocumentClass");
            m_UIConfig.documentClass.DockNodeFlagsOverrideSet = 0;
            m_UIConfig.documentClass.DockingAllowUnclassed = false;

            m_UIConfig.projectSettingsClass.ClassId = ImGui::GetID("ProjectSettingsClass");
            m_UIConfig.projectSettingsClass.DockingAllowUnclassed = false;
            m_UIConfig.projectSettingsClass.DockNodeFlagsOverrideSet = 0;

            m_UIConfig.documentDockSpace = ImGui::GetID("DocumentDockSpace");
            m_UIConfig.projectSettingsDockSpace = ImGui::GetID("ProjectSettingsDockSpace");
        }

        // Set the top level dock space
        {
            m_UIConfig.editorTopLevelDockSpace = ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_None, &m_UIConfig.editorTopLevelClass);
        }

#if 0
        static bool dockspaceOpen = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);

        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();
        float minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x = 370.0f;

        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("EditorDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        io.ConfigWindowsMoveFromTitleBarOnly = true;

        style.WindowMinSize.x = minWinSizeX;

        ImGui::End();
#endif
    }

    const EditorUIConfig& EditorLayer::GetUIConfig() const
    {
        return m_UIConfig;
    }

    EditorUIConfig& EditorLayer::GetUIConfig()
    {
        return m_UIConfig;
    }


}
