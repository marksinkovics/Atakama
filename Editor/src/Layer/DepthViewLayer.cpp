#include "DepthViewLayer.hpp"

#include <Atakama/Engine/Engine.hpp>
#include <Atakama/Engine/RenderPass/RenderPass.hpp>
#include <Atakama/Engine/RenderPass/DepthViewRenderPass.hpp>
#include <Atakama/Engine/FrameBuffer.hpp>
#include <Atakama/Engine/Texture.hpp>

namespace Atakama::Editor
{

DepthViewLayer::DepthViewLayer()
    : Layer("Depth View Layer"), m_UIConfig(GetUIConfig())
{
    m_Engine = g_RuntimeGlobalContext.m_Engine;
    m_RenderPass = m_Engine->GetDepthViewRenderPass();
}

void DepthViewLayer::OnUpdateUI(float ts)
{
    if (!GetWindowConfig(WindowId::DepthView).Open)
        return;

    ImGui::SetNextWindowClass(&m_UIConfig.documentClass);
    ImGui::Begin(GetImGuiWindowId(WindowId::DepthView).c_str());
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImVec2 wSize = ImGui::GetContentRegionAvail();
    Ref<Texture> texture = m_RenderPass->GetOutputColorTexture();
    if (texture)
        ImGui::Image(reinterpret_cast<ImTextureID>(texture->GetId()), wSize, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::PopStyleVar();
    ImGui::End();

}

}
