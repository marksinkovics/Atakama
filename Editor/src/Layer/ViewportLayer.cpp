#include "ViewportLayer.hpp"

#include <Atakama/Core/Application.hpp>
#include <Atakama/Core/InputSystem.hpp>
#include <Atakama/Engine/AssetManager.hpp>
#include <Atakama/Engine/RenderPass/RenderPass.hpp>
#include <Atakama/Engine/RenderPass/OutlineRenderPass.hpp>
#include <Atakama/Engine/FrameBuffer.hpp>

#include <imgui.h>

namespace Atakama::Editor
{

ViewportLayer::ViewportLayer()
: Layer("Viewport Layer")
{
    m_Engine = g_RuntimeGlobalContext.m_Engine;
    m_RenderPass = m_Engine->GetOutlineRenderPass();
    m_Callback = std::bind(&Engine::UpdateRenderingViewportSize, *m_Engine, std::placeholders::_1);
}

void ViewportLayer::OnAttach()
{
}

void ViewportLayer::OnUpdateUI(float ts)
{
    if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && m_Callback)
    {
        m_Callback(m_ViewportSize);
    }

    ImGui::Begin("Viewport");
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Text("Selected mesh: %d", m_MeshId);
    ImVec2 vMin = ImGui::GetWindowContentRegionMin();
    ImVec2 vMax = ImGui::GetWindowContentRegionMax();

    vMin.x += ImGui::GetWindowPos().x;
    vMin.y += ImGui::GetWindowPos().y;
    vMax.x += ImGui::GetWindowPos().x;
    vMax.y += ImGui::GetWindowPos().y;

    if (m_ViewportFocused && !ImGui::IsWindowFocused()) {
        g_RuntimeGlobalContext.m_InputSystem->ClearKeyboardEvents();
    }

    m_ViewportFocused = ImGui::IsWindowFocused();
    m_ViewportHovered = ImGui::IsMouseHoveringRect(vMin, vMax);
    g_RuntimeGlobalContext.m_Application->BlockEvent(!(m_ViewportFocused && m_ViewportHovered));

    ImVec2 wSize = ImGui::GetContentRegionAvail();
    float scale = ImGui::GetMainViewport()->DpiScale;
    m_ViewportSize = { wSize.x * scale, wSize.y * scale };

    m_ViewportBounds[0] = {vMin.x, vMin.y};
    m_ViewportBounds[1] = {vMax.x, vMax.y};

    auto[mx, my] = ImGui::GetMousePos();
    mx -= m_ViewportBounds[0].x;
    my -= m_ViewportBounds[0].y;
    glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
    my = viewportSize.y - my;
    int mouseX = (int)mx;
    int mouseY = (int)my;

    if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
    {
        m_MeshId = m_RenderPass->GetFrameBuffer()->ReadInt(1, mouseX * scale, mouseY * scale);
        Atakama::AssetManager::Get()->SetSelectedMeshId(m_MeshId);
    }

    Ref<Texture> texture = m_RenderPass->GetOutputColorTexture();
    if (texture)
        ImGui::Image(reinterpret_cast<ImTextureID>(texture->GetId()), wSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::PopStyleVar();
    ImGui::End();
}

}
