#include "DebugRenderPass.hpp"

#include "Atakama/Asset/AssetManager.hpp"
#include "Atakama/Core/FileSystem.hpp"
#include "Atakama/Engine/RenderSystem.hpp"

#include "Atakama/Scene/Scene.hpp"
#include "Atakama/Engine/Camera.hpp"
#include "Atakama/Scene/Entity.hpp"
#include "Atakama/Scene/Components/Components.hpp"

namespace Atakama
{

DebugRenderPass::DebugRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene> scene)
: SceneRenderPass(renderSystem, scene)
{
    m_SimpleShader = CreateRef<Shader>(FileSystem::GetShaderFile("simple_shader.vert"), FileSystem::GetShaderFile("simple_shader.frag"));
    m_PointLightShader = CreateRef<Shader>(FileSystem::GetShaderFile("point_light.vert"), FileSystem::GetShaderFile("point_light.frag"));
    m_GridShader = CreateRef<Shader>(FileSystem::GetShaderFile("grid.vert"), FileSystem::GetShaderFile("grid.frag"));
    m_Grid = AssetManager::Get()->GetMeshById("grid");
}

void DebugRenderPass::Draw()
{
    Entity cameraEntity = m_Scene->GetPrimaryCameraEntity();
    Camera& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
    auto& cameraTransform = cameraEntity.GetComponent<TransformComponent>();

    Entity lightEntity = m_Scene->GetLight();
    PointLightComponent& lightLightComponent = lightEntity.GetComponent<PointLightComponent>();
    TransformComponent& lightTransformComponent = lightEntity.GetComponent<TransformComponent>();
    MeshComponent& lightMeshComponent = lightEntity.GetComponent<MeshComponent>();


    m_SimpleShader->Bind();
    m_SimpleShader->SetUniformMat4("uView", camera.GetViewMatrix(cameraTransform));
    m_SimpleShader->SetUniformMat4("uProjection", camera.GetProjectionMatrix());
    m_SimpleShader->SetUniformInt("u_SelectedMeshId", m_Scene->GetSelectedEntity());


    auto view = m_Scene->GetRegistry().view<MeshComponent, DebugComponent>(entt::exclude<PointLightComponent, SkyBoxComponent>);
    for (auto entityId : view)
    {
        const MeshComponent& meshComponent = view.get<MeshComponent>(entityId);
        Entity entity { entityId, m_Scene.get() };
        m_RenderSystem->Draw(entity, m_SimpleShader);
    }

    m_SimpleShader->Unbind();


    m_PointLightShader->Bind();
    m_PointLightShader->SetUniformMat4("uView", camera.GetViewMatrix(cameraTransform));
    m_PointLightShader->SetUniformMat4("uProjection", camera.GetProjectionMatrix());
    // Lights
    m_PointLightShader->SetUniformFloat4("uLightPosition", glm::vec4(lightTransformComponent.Translate, 1.0f));
    m_PointLightShader->SetUniformFloat4("uLightColor", lightLightComponent.Color);
    // Camera / View
    m_PointLightShader->SetUniformFloat3("uViewPosition", cameraTransform.Translate);
    // Mesh
    m_PointLightShader->SetUniformInt("u_SelectedMeshId", m_Scene->GetSelectedEntity());

    m_RenderSystem->Draw(lightEntity, m_PointLightShader);

    m_PointLightShader->Unbind();


    // Drawing grid
    m_GridShader->Bind();
    m_GridShader->SetUniformMat4("uView", camera.GetViewMatrix(cameraTransform));
    m_GridShader->SetUniformMat4("uProjection", camera.GetProjectionMatrix());
    m_GridShader->SetUniformFloat4("uCameraPos", glm::vec4(cameraTransform.Translate, 1.0f));

    m_RenderSystem->Draw(m_Grid, m_GridShader);
    m_GridShader->Unbind();
}

std::string DebugRenderPass::GetName()
{
    return "Debug RenderPass";
}

}
