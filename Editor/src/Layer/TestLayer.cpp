#include "TestLayer.hpp"

#include "EditorApplication.hpp"


#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

namespace Atakama::Editor
{

TestLayer::TestLayer()
: Layer("Stats Layer")
{
    m_Application = (EditorApplication*)g_RuntimeGlobalContext.m_Application;
}

void TestLayer::OnAttach()
{

}

void TestLayer::OnDetach()
{

}

ImVec2 operator-(const ImVec2 lhs, const ImVec2 rhs) {
    return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

ImVec2 operator+(const ImVec2 lhs, const ImVec2 rhs) {
    return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
}


void TestLayer::OnUpdateUI(float ts)
{
    const float toolbarSize = 25;
    float menuBarHeight = 0.f;

    // Menubar
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File")) 
            {
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

#if 1
    {

        ImGuiWindowClass top_level_class;
        top_level_class.ClassId = ImGui::GetID("MyTopLevelClass");
        top_level_class.DockingAllowUnclassed = false;
        top_level_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoDockingSplitOther | ImGuiDockNodeFlags_NoDockingSplitMe;

        ImGuiWindowClass inside_document_class;
        inside_document_class.ClassId = ImGui::GetID("InsideDocumentClass");
        inside_document_class.DockNodeFlagsOverrideSet = 0;
        inside_document_class.DockingAllowUnclassed = false;

        ImGuiWindowClass project_settings_class;
        project_settings_class.ClassId = ImGui::GetID("ProjectSettingsClass");
        project_settings_class.DockingAllowUnclassed = false;
        project_settings_class.DockNodeFlagsOverrideSet = 0;

        ImGuiID mainDockspaceId = ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_None, &top_level_class);

        ImGuiID insideDocumentDockSpace = ImGui::GetID("InsideDocumentDockSpace");
        ImGuiID projectSettingsDockSpace = ImGui::GetID("ProjectSettingsDockSpace");

        ImGui::SetNextWindowClass(&top_level_class);
        ImGui::Begin("ThirdPersonView");
        ImGui::BeginChild("statusbar", ImVec2(ImGui::GetContentRegionAvail().x, toolbarSize));
        ImGui::Text("[STATUS BAR]"); ImGui::SameLine(); ImGui::Button("Toolbar goes here", ImVec2(0, toolbarSize));
        ImGui::EndChild();
        ImGui::DockSpace(insideDocumentDockSpace, ImVec2(0, 0), 0, &inside_document_class);
        ImGui::End();

        ImGui::SetNextWindowClass(&top_level_class);
        ImGui::Begin("Project Settings");
        ImGui::DockSpace(projectSettingsDockSpace, ImVec2(0, 0), 0, &project_settings_class);
        ImGui::End();


        static bool first_time = true;
        if (first_time) {
            first_time = false;

            ImGuiViewport* viewport = ImGui::GetMainViewport();

            ImVec2 workSize = ImGui::GetMainViewport()->WorkSize;
            ImVec2 workPos = ImGui::GetMainViewport()->WorkPos;
            ImGui::DockBuilderRemoveNode(mainDockspaceId); // Clear out existing layout
            ImGui::DockBuilderAddNode(mainDockspaceId, ImGuiDockNodeFlags_None); // Add empty node
            ImGui::DockBuilderSetNodeSize(mainDockspaceId, workSize);
            ImGui::DockBuilderSetNodePos(mainDockspaceId, workPos);

            ImGui::DockBuilderDockWindow("ThirdPersonView", mainDockspaceId);
            ImGui::DockBuilderDockWindow("Project Settings", mainDockspaceId);

            ImGui::DockBuilderFinish(mainDockspaceId);

            {
                ImGui::DockBuilderSetNodeSize(insideDocumentDockSpace, ImGui::GetMainViewport()->WorkSize);
                auto insideDocumentUp = ImGui::DockBuilderSplitNode(insideDocumentDockSpace, ImGuiDir_Up, 0.1f, nullptr, &insideDocumentDockSpace);
                auto insideDocumentLeft = ImGui::DockBuilderSplitNode(insideDocumentDockSpace, ImGuiDir_Left, 0.5f, nullptr, &insideDocumentDockSpace);
                auto componentsBottom = ImGui::DockBuilderSplitNode(insideDocumentLeft, ImGuiDir_Down, 0.5f, nullptr, &insideDocumentLeft);
                ImGui::DockBuilderDockWindow("Components", insideDocumentLeft);
                ImGui::DockBuilderDockWindow("Properties", componentsBottom);
                ImGui::DockBuilderFinish(insideDocumentDockSpace);
            }

            {
                ImGui::DockBuilderSetNodeSize(projectSettingsDockSpace, ImGui::GetMainViewport()->WorkSize);
                auto projectSettingsRight = ImGui::DockBuilderSplitNode(projectSettingsDockSpace, ImGuiDir_Down, 0.5f, nullptr, &projectSettingsDockSpace);
                ImGui::DockBuilderDockWindow("Categories", projectSettingsRight);
                ImGui::DockBuilderFinish(projectSettingsDockSpace);
            }

        }


        ImGui::SetNextWindowClass(&inside_document_class);
        ImGui::Begin("Components");
        ImGui::End();

        ImGui::SetNextWindowClass(&inside_document_class);
        ImGui::Begin("Properties");
        ImGui::End();

        ImGui::SetNextWindowClass(&project_settings_class);
        ImGui::Begin("Categories");
        ImGui::End();
    }

#endif

}

}

