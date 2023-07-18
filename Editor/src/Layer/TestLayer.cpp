#include "TestLayer.hpp"

#include "EditorApplication.hpp"

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

    // Generate IDs
    {

        editorTopLevelClass.ClassId = ImGui::GetID("MyTopLevelClass");
        editorTopLevelClass.DockingAllowUnclassed = false;
        editorTopLevelClass.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoDockingSplitOther | ImGuiDockNodeFlags_NoDockingSplitMe;

        documentClass.ClassId = ImGui::GetID("DocumentClass");
        documentClass.DockNodeFlagsOverrideSet = 0;
        documentClass.DockingAllowUnclassed = false;

        projectSettingsClass.ClassId = ImGui::GetID("ProjectSettingsClass");
        projectSettingsClass.DockingAllowUnclassed = false;
        projectSettingsClass.DockNodeFlagsOverrideSet = 0;

        documentDockSpace = ImGui::GetID("DocumentDockSpace");
        projectSettingsDockSpace = ImGui::GetID("ProjectSettingsDockSpace");
    }
    
    {
        editorTopLevelDockSpace = ImGui::DockSpaceOverViewport(NULL, ImGuiDockNodeFlags_None, &editorTopLevelClass);
    }

    {
        ImGui::SetNextWindowClass(&editorTopLevelClass);
        ImGui::Begin("Document");
        ImGui::BeginChild("statusbar", ImVec2(ImGui::GetContentRegionAvail().x, toolbarSize));
        ImGui::Text("[STATUS BAR]"); ImGui::SameLine(); ImGui::Button("Toolbar goes here", ImVec2(0, toolbarSize));
        ImGui::EndChild();
        ImGui::DockSpace(documentDockSpace, ImVec2(0, 0), 0, &documentClass);
        ImGui::End();

    }
    
    {
        ImGui::SetNextWindowClass(&editorTopLevelClass);
        ImGui::Begin("Project Settings");
        ImGui::DockSpace(projectSettingsDockSpace, ImVec2(0, 0), 0, &projectSettingsClass);
        ImGui::End();
    }
    
    {
        static bool first_time = true;
        if (first_time) {
            first_time = false;

            ImGuiViewport* viewport = ImGui::GetMainViewport();

            ImVec2 workSize = ImGui::GetMainViewport()->WorkSize;
            ImVec2 workPos = ImGui::GetMainViewport()->WorkPos;
            ImGui::DockBuilderRemoveNode(editorTopLevelDockSpace); // Clear out existing layout
            ImGui::DockBuilderAddNode(editorTopLevelDockSpace, ImGuiDockNodeFlags_None); // Add empty node
            ImGui::DockBuilderSetNodeSize(editorTopLevelDockSpace, workSize);
            ImGui::DockBuilderSetNodePos(editorTopLevelDockSpace, workPos);

            ImGui::DockBuilderDockWindow("Document", editorTopLevelDockSpace);
            ImGui::DockBuilderDockWindow("Project Settings", editorTopLevelDockSpace);

            ImGui::DockBuilderFinish(editorTopLevelDockSpace);

            {
                ImGui::DockBuilderSetNodeSize(documentDockSpace, ImGui::GetMainViewport()->WorkSize);
                auto insideDocumentUp = ImGui::DockBuilderSplitNode(documentDockSpace, ImGuiDir_Up, 0.1f, nullptr, &documentDockSpace);
                auto insideDocumentLeft = ImGui::DockBuilderSplitNode(documentDockSpace, ImGuiDir_Left, 0.5f, nullptr, &documentDockSpace);
                auto componentsBottom = ImGui::DockBuilderSplitNode(insideDocumentLeft, ImGuiDir_Down, 0.5f, nullptr, &insideDocumentLeft);
                ImGui::DockBuilderDockWindow("Components", insideDocumentLeft);
                ImGui::DockBuilderDockWindow("Properties", componentsBottom);
                ImGui::DockBuilderFinish(documentDockSpace);
            }

            {
                ImGui::DockBuilderSetNodeSize(projectSettingsDockSpace, ImGui::GetMainViewport()->WorkSize);
                auto projectSettingsRight = ImGui::DockBuilderSplitNode(projectSettingsDockSpace, ImGuiDir_Down, 0.5f, nullptr, &projectSettingsDockSpace);
                ImGui::DockBuilderDockWindow("Categories", projectSettingsRight);
                ImGui::DockBuilderFinish(projectSettingsDockSpace);
            }

        }

    }
    {
        ImGui::SetNextWindowClass(&documentClass);
        ImGui::Begin("Components");
        ImGui::End();
    } 
    {
        ImGui::SetNextWindowClass(&documentClass);
        ImGui::Begin("Properties");
        ImGui::End();
    } 
    {
        ImGui::SetNextWindowClass(&projectSettingsClass);
        ImGui::Begin("Categories");
        ImGui::End();
    }

}

}

