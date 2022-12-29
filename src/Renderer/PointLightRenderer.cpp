#include "PointLightRenderer.hpp"
#include "FileSystem.hpp"
#include "Engine/SubMesh.hpp"
#include "Engine/AssetManager.hpp"

namespace OGLSample
{

void PointLightRenderer::Init(Ref<RenderSystem> renderSystem, Ref<Camera> camera)
{
    Ref<Shader> shader = CreateRef<Shader>(FileSystem::GetShaderFile("point_light.vert"), FileSystem::GetShaderFile("point_light.frag"));
    Renderer::Init(renderSystem, camera, shader);
}

void PointLightRenderer::Draw(Ref<PointLight> light)
{
    light->GetMesh()->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(light->GetPosition())));

    m_Shader->SetUniformMat4("uView", m_Camera->GetViewMatrix());
    m_Shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());
    // Lights
    m_Shader->SetUniformFloat4("uLightPosition", light->GetPosition());
    m_Shader->SetUniformFloat4("uLightColor", light->GetColor());
    // Camera / View
    m_Shader->SetUniformFloat3("uViewPosition", m_Camera->GetPosition());

    light->GetMesh()->Draw(m_RenderSystem, m_Shader);
}

}
