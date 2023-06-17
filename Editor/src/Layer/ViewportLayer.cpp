#include "ViewportLayer.hpp"

#include <Atakama/Core/Application.hpp>
#include <Atakama/Core/InputSystem.hpp>
#include <Atakama/Engine/AssetManager.hpp>
#include <Atakama/Engine/RenderPass/RenderPass.hpp>
#include <Atakama/Engine/RenderPass/OutlineRenderPass.hpp>
#include <Atakama/Engine/FrameBuffer.hpp>


#include <Atakama/Scene/Scene.hpp>
#include <Atakama/Scene/Entity.hpp>
#include <Atakama/Engine/Camera.hpp>
#include <Atakama/Scene/Components/Components.hpp>

#include <imgui.h>
#include <ImGuizmo.h>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace Atakama::Editor
{

ViewportLayer::ViewportLayer()
: Layer("Viewport Layer"), m_GizmoType(-1)
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

    ImVec2 vMin = ImGui::GetWindowContentRegionMin();
    ImVec2 vMax = ImGui::GetWindowContentRegionMax();

    vMin.x += ImGui::GetWindowPos().x;
    vMin.y += ImGui::GetWindowPos().y;
    vMax.x += ImGui::GetWindowPos().x;
    vMax.y += ImGui::GetWindowPos().y;

    // Fixes a bug where the user clicked or hovered out of the window
    if ((m_ViewportFocused && !ImGui::IsWindowFocused()) || (m_ViewportHovered && !ImGui::IsMouseHoveringRect(vMin, vMax))) {
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

        if (g_RuntimeGlobalContext.m_InputSystem->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
            Entity entity = Entity(static_cast<entt::entity>(m_MeshId), m_Engine->GetScene().get());
            m_Engine->GetScene()->SetSelectedEntity(entity);
        }
    }

    Ref<Texture> texture = m_RenderPass->GetOutputColorTexture();
    if (texture)
        ImGui::Image(reinterpret_cast<ImTextureID>(texture->GetId()), wSize, ImVec2(0, 1), ImVec2(1, 0));


    //TODO: fetch the titlebar height and adjust the Y coordinate
    ImGui::SetCursorPos(ImVec2(20, 40));
    ImGui::BeginGroup();
    ImGui::RadioButton("Select", &m_GizmoType, -1);
    ImGui::RadioButton("Rotate", &m_GizmoType, ImGuizmo::OPERATION::ROTATE);
    ImGui::RadioButton("Translate", &m_GizmoType, ImGuizmo::OPERATION::TRANSLATE);
    ImGui::RadioButton("Scale", &m_GizmoType, ImGuizmo::OPERATION::SCALE);
    ImGui::NewLine();
    ImGui::Text("Mesh: %d", m_MeshId);
    ImGui::EndGroup();

    //ImGuizmo
    Entity selectedEntity = m_Engine->GetScene()->GetSelectedEntity();
    if (selectedEntity.IsValid() && m_GizmoType != -1)
    {
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();

        ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y - m_ViewportBounds[0].y);

        // Editor camera
        Entity cameraEntity = m_Engine->GetScene()->GetPrimaryCameraEntity();
        Camera& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
        auto& cameraTransform = cameraEntity.GetComponent<TransformComponent>();
        glm::mat4 cameraView = camera.GetViewMatrix(cameraTransform);
        const glm::mat4& cameraProjection = camera.GetProjectionMatrix();


        //Entity
        auto& tc = selectedEntity.GetComponent<TransformComponent>();
        glm::mat4 transform = tc.GetMat4();

        bool snap = g_RuntimeGlobalContext.m_InputSystem->IsKeyPressed(GLFW_KEY_LEFT_CONTROL);
        float snapValue = 0.5f; // Snap to 0.5m for translation/scale
        // Snap to 45 degrees for rotation
        if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
            snapValue = 5.0f;
        float snapValues[3] = { snapValue, snapValue, snapValue };

        ImGuizmo::Manipulate(
            glm::value_ptr(cameraView), // view
            glm::value_ptr(cameraProjection), // projection
            (ImGuizmo::OPERATION)m_GizmoType, // operation
            ImGuizmo::LOCAL, // mode
            glm::value_ptr(transform), //matrix
            nullptr, // delta matrix
            snap ? snapValues : nullptr // snap
            // localBounds
            // boundsSnap
        );

        g_RuntimeGlobalContext.m_Application->BlockEvent(ImGuizmo::IsUsing());
        if (ImGuizmo::IsUsing())
        {
            glm::vec3 translation, rotation, scale;
            ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), glm::value_ptr(translation), glm::value_ptr(rotation), glm::value_ptr(scale));
            tc.Translate = translation;
            tc.Rotation = glm::radians(rotation);
            tc.Scale = scale;
        }
    }

    ImGui::PopStyleVar();
    ImGui::End();
}

}
