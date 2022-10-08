#include "SimpleRenderer.hpp"

#include "FileSystem.hpp"

namespace OGLSample
{

void SimpleRenderer::Init(Ref<Camera> camera)
{
    Ref<Shader> shader = CreateRef<Shader>(FileSystem::GetShaderFile("simple_shader.vert"), FileSystem::GetShaderFile("simple_shader.frag"));
    Renderer::Init(camera, shader);
}

void SimpleRenderer::Draw(Ref<Model> model)
{
    m_Shader->SetUniformMat4("uModel", model->GetModelMatrix());
    m_Shader->SetUniformMat4("uView", m_Camera->GetViewMatrix());
    m_Shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());

    model->Draw();
}

}