#include "LightingRenderer.hpp"
#include "FileSystem.hpp"
#include "Engine/AssetManager.hpp"

namespace Atakama
{

LightingRenderer::LightingRenderer(Ref<RenderSystem> renderSystem, Ref<Camera>& camera)
: Renderer(renderSystem, camera, CreateRef<Shader>(FileSystem::GetShaderFile("lighting_shader.vert"), FileSystem::GetShaderFile("lighting_shader.frag")))
{
}

void LightingRenderer::Begin(Ref<PointLight> light)
{
    Renderer::Begin();
    m_Light = light;
}

void LightingRenderer::Draw(Ref<Mesh> mesh)
{
    m_Shader->SetUniformMat4("uView", m_Camera->GetViewMatrix());
    m_Shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());

    // Lights
    m_Shader->SetUniformFloat4("uLightPosition", m_Light->GetPosition());
    m_Shader->SetUniformFloat4("uLightColor", m_Light->GetColor());
    // Camera / View
    m_Shader->SetUniformFloat3("uViewPosition", m_Camera->Transform.Translate);
    // Mesh
    m_Shader->SetUniformInt("u_SelectedMeshId", AssetManager::Get()->GetSelectedMeshId());

    mesh->Draw(m_RenderSystem, m_Shader);
}

}
