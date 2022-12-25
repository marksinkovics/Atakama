#include "SimpleRenderer.hpp"
#include "FileSystem.hpp"

namespace OGLSample
{

void SimpleRenderer::Init(Ref<RenderSystem> renderSystem, Ref<Camera> camera)
{
    Ref<Shader> shader = Shader::Create(FileSystem::GetShaderFile("simple_shader.vert"), FileSystem::GetShaderFile("simple_shader.frag"));
    Renderer::Init(renderSystem, camera, shader);
}

void SimpleRenderer::Draw(Ref<Mesh> mesh)
{
    m_Shader->SetUniformMat4("uView", m_Camera->GetViewMatrix());
    m_Shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());
    mesh->Draw(m_RenderSystem, m_Shader);
}

}
