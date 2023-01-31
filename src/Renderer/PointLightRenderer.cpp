#include "PointLightRenderer.hpp"
#include "FileSystem.hpp"
#include "Engine/SubMesh.hpp"
#include "Engine/AssetManager.hpp"

namespace OGLSample
{

PointLightRenderer::PointLightRenderer(Ref<RenderSystem> renderSystem, Ref<Camera>& camera)
: Renderer(renderSystem, camera, CreateRef<Shader>(FileSystem::GetShaderFile("point_light.vert"), FileSystem::GetShaderFile("point_light.frag")))
{
}

void PointLightRenderer::Draw(Ref<PointLight> light)
{
    light->GetMesh()->GetTransform()->Translate = glm::vec3(light->GetPosition());

    m_Shader->SetUniformMat4("uView", m_Camera->GetViewMatrix());
    m_Shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());
    // Lights
    m_Shader->SetUniformFloat4("uLightPosition", light->GetPosition());
    m_Shader->SetUniformFloat4("uLightColor", light->GetColor());
    // Camera / View
    m_Shader->SetUniformFloat3("uViewPosition", m_Camera->Transform.Translate);
    // Mesh
    m_Shader->SetUniformInt("u_SelectedMeshId", AssetManager::Get()->GetSelectedMeshId());

    light->GetMesh()->Draw(m_RenderSystem, m_Shader);
}

}
