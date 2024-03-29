#include "StatsLayer.hpp"

#include "RuntimeApplication.hpp"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

namespace Atakama::Runtime
{

StatsLayer::StatsLayer()
: Layer("Stats Layer")
{
    m_Application = g_RuntimeGlobalContext.m_Application;
}

void StatsLayer::OnAttach()
{

}

void StatsLayer::OnDetach()
{

}

void StatsLayer::OnUpdateUI(float ts)
{
    ImGui::Begin("Stats");
    ImGui::Text("Vendor: %s", m_Application->GetEngine()->GetStatistics().Vendor.c_str());
    ImGui::Text("Renderer: %s", m_Application->GetEngine()->GetStatistics().Renderer.c_str());
    ImGui::Text("Version: %s", m_Application->GetEngine()->GetStatistics().Version.c_str());
    ImGui::Text("GLSL Version: %s", m_Application->GetEngine()->GetStatistics().ShadingLanguageVersion.c_str());
    ImGui::Text("CPU time: %f ms", m_Application->GetEngine()->GetStatistics().CPUTime);
    ImGui::Text("GPU time: %f ms", m_Application->GetEngine()->GetStatistics().GPUTime);
    ImGui::Text("AVG %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

}
