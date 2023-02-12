#include "DebugRenderPass.hpp"

#include "Atakama/Engine/AssetManager.hpp"
#include "Atakama/Core/FileSystem.hpp"

#include "Atakama/Scene/Scene.hpp"
#include "Atakama/Engine/Camera.hpp"
#include "Atakama/Scene/Entity.hpp"
#include "Atakama/Scene/Components/Components.hpp"

namespace Atakama
{

DebugRenderPass::DebugRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene> scene)
: SceneRenderPass(renderSystem, scene), m_AxisMesh(AssetManager::Get()->LoadAxis())
{
    m_SimpleShader = CreateRef<Shader>(FileSystem::GetShaderFile("simple_shader.vert"), FileSystem::GetShaderFile("simple_shader.frag"));
    m_PointLightShader = CreateRef<Shader>(FileSystem::GetShaderFile("point_light.vert"), FileSystem::GetShaderFile("point_light.frag"));
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
    m_SimpleShader->SetUniformInt("u_SelectedMeshId", AssetManager::Get()->GetSelectedMeshId());
    m_AxisMesh->Draw(m_RenderSystem, m_SimpleShader);
    m_SimpleShader->Unbind();


    m_PointLightShader->Bind();
    lightMeshComponent.Mesh->GetTransform()->Translate = lightTransformComponent.Translate;
    m_PointLightShader->SetUniformMat4("uView", camera.GetViewMatrix(cameraTransform));
    m_PointLightShader->SetUniformMat4("uProjection", camera.GetProjectionMatrix());
    // Lights
    m_PointLightShader->SetUniformFloat4("uLightPosition", glm::vec4(lightTransformComponent.Translate, 1.0f));
    m_PointLightShader->SetUniformFloat4("uLightColor", lightLightComponent.Color);
    // Camera / View
    m_PointLightShader->SetUniformFloat3("uViewPosition", cameraTransform.Translate);
    // Mesh
    m_PointLightShader->SetUniformInt("u_SelectedMeshId", AssetManager::Get()->GetSelectedMeshId());
    lightMeshComponent.Mesh->Draw(m_RenderSystem, m_PointLightShader);
    m_PointLightShader->Unbind();
}

std::string DebugRenderPass::GetName()
{
    return "Debug RenderPass";
}

}
