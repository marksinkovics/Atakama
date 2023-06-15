#include "MenuBarLayer.hpp"

#include <Atakama/Engine/AssetManager.hpp>
#include <Atakama/Engine/Engine.hpp>
#include <Atakama/Scene/Scene.hpp>

#include <imgui.h>

namespace Atakama::Editor
{

MenuBarLayer::MenuBarLayer()
{
}

void MenuBarLayer::OnUpdateUI(float ts)
{
    if(g_RuntimeEditorContext.DemoWindowOpen)
    {
        ImGui::ShowDemoWindow();
    }

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open", "CTRL+O")) {}
            if (ImGui::MenuItem("Save", "CTRL+S")) {}
            if (ImGui::MenuItem("Import model", nullptr)) {
                m_fileDialogOpen = true;
                m_fileDialogInfo.type = FileDialogInfo::Type::OpenFile;
                m_fileDialogInfo.title = "Import model";
                m_fileDialogInfo.directoryPath = std::filesystem::current_path();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window"))
        {
            if (ImGui::MenuItem("Stats", nullptr, &g_RuntimeEditorContext.StatshWindowOpen)) {}
            if (ImGui::MenuItem("Depth", nullptr, &g_RuntimeEditorContext.DepthWindowOpen)) {}
            if (ImGui::MenuItem("Demo", nullptr, &g_RuntimeEditorContext.DemoWindowOpen)) {}
            if (ImGui::MenuItem("Scene View", nullptr, &g_RuntimeEditorContext.SceneViewOpen)) {}
            if (ImGui::MenuItem("Object Properties", nullptr, &g_RuntimeEditorContext.ObjectPropertiesViewOpen)) {}
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if (ImGui::FileDialog(&m_fileDialogOpen, &m_fileDialogInfo))
    {
        g_RuntimeGlobalContext.m_AssetManager->ImportModel(m_fileDialogInfo.resultPath);
        g_RuntimeGlobalContext.m_Engine->GetScene()->AddModeById(m_fileDialogInfo.resultPath.filename().string());
    }
}

}
