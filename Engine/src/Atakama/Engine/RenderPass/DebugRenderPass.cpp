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
    auto& transform = cameraEntity.GetComponent<TransformComponent>();

    m_SimpleShader->Bind();
    m_SimpleShader->SetUniformMat4("uView", camera.GetViewMatrix(transform));
    m_SimpleShader->SetUniformMat4("uProjection", camera.GetProjectionMatrix());
    m_SimpleShader->SetUniformInt("u_SelectedMeshId", AssetManager::Get()->GetSelectedMeshId());
    m_AxisMesh->Draw(m_RenderSystem, m_SimpleShader);
    m_SimpleShader->Unbind();


    m_PointLightShader->Bind();
    m_Scene->GetLight()->GetMesh()->GetTransform()->Translate = glm::vec3(m_Scene->GetLight()->GetPosition());
    m_PointLightShader->SetUniformMat4("uView", camera.GetViewMatrix(transform));
    m_PointLightShader->SetUniformMat4("uProjection", camera.GetProjectionMatrix());
    // Lights
    m_PointLightShader->SetUniformFloat4("uLightPosition", m_Scene->GetLight()->GetPosition());
    m_PointLightShader->SetUniformFloat4("uLightColor", m_Scene->GetLight()->GetColor());
    // Camera / View
    m_PointLightShader->SetUniformFloat3("uViewPosition", transform.Translate);
    // Mesh
    m_PointLightShader->SetUniformInt("u_SelectedMeshId", AssetManager::Get()->GetSelectedMeshId());
    m_Scene->GetLight()->GetMesh()->Draw(m_RenderSystem, m_PointLightShader);
    m_PointLightShader->Unbind();
}

std::string DebugRenderPass::GetName()
{
    return "Debug RenderPass";
}

}
