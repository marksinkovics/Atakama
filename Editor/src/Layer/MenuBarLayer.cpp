#include "MenuBarLayer.hpp"

#include <imgui.h>

namespace Atakama::Editor
{

MenuBarLayer::MenuBarLayer()
{

}



void MenuBarLayer::OnUpdateUI(float ts)
{

    if(g_RuntimeEditorContext.DemohWindowOpen)
    {
        ImGui::ShowDemoWindow();
    }

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open", "CTRL+O")) {}
            if (ImGui::MenuItem("Save", "CTRL+S")) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window"))
        {
            if (ImGui::MenuItem("Stats", nullptr, &g_RuntimeEditorContext.StatshWindowOpen)) {}
            if (ImGui::MenuItem("Depth", nullptr, &g_RuntimeEditorContext.DepthWindowOpen)) {}
            if (ImGui::MenuItem("Demo", nullptr, &g_RuntimeEditorContext.DemohWindowOpen)) {}
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

}

}
