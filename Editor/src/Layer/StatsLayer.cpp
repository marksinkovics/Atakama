#include "StatsLayer.hpp"

#include "EditorApplication.hpp"


#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

namespace Atakama::Editor
{

StatsLayer::StatsLayer()
: Layer("Stats Layer")
{
    m_Application = (EditorApplication*)g_RuntimeGlobalContext.m_Application;
}

void StatsLayer::OnAttach()
{

}

void StatsLayer::OnDetach()
{

}

void StatsLayer::OnUpdateUI(float ts)
{
    if (!g_RuntimeEditorContext.StatshWindowOpen)
        return;

    ImGui::Begin("Stats");
    ImGui::Text("CPU time: %f ms", m_Application->GetProfiler()->GetCPUTime());
    ImGui::Text("GPU time: %f ms", m_Application->GetProfiler()->GetGPUTime());
    ImGui::Text("AVG %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

}
