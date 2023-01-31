#include "SimpleRenderer.hpp"
#include "FileSystem.hpp"
#include "Engine/AssetManager.hpp"

namespace OGLSample
{

SimpleRenderer::SimpleRenderer(Ref<RenderSystem> renderSystem, Ref<Camera>& camera)
: Renderer(renderSystem, camera, CreateRef<Shader>(FileSystem::GetShaderFile("simple_shader.vert"), FileSystem::GetShaderFile("simple_shader.frag")))
{
}

void SimpleRenderer::Draw(Ref<Mesh> mesh)
{
    m_Shader->SetUniformMat4("uView", m_Camera->GetViewMatrix());
    m_Shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());
    // Mesh
    m_Shader->SetUniformInt("u_SelectedMeshId", AssetManager::Get()->GetSelectedMeshId());
    mesh->Draw(m_RenderSystem, m_Shader);
}

}
