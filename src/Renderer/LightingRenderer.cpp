#include "LightingRenderer.hpp"
#include "FileSystem.hpp"

namespace OGLSample
{

void LightingRenderer::Init(Ref<Camera> camera)
{
    Ref<Shader> shader = CreateRef<Shader>(FileSystem::GetShaderFile("lighting_shader.vert"), FileSystem::GetShaderFile("lighting_shader.frag"));
    Renderer::Init(camera, shader);
}

void LightingRenderer::Begin(glm::vec4 lightPosition, glm::vec4 lightColor)
{
    Renderer::Begin();
    m_LightPosition = lightPosition;
    m_LightColor = lightColor;
}

void LightingRenderer::Draw(Ref<Model> model)
{
    m_Shader->SetUniformMat4("uModel", model->GetModelMatrix());
    m_Shader->SetUniformMat4("uView", m_Camera->GetViewMatrix());
    m_Shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());
    m_Shader->SetUniformMat3("uNormalMatrix", model->GetNormalMatrix());
    // Lights
    m_Shader->SetUniformFloat4("uLightPosition", m_LightPosition);
    m_Shader->SetUniformFloat4("uLightColor", m_LightColor);
    // Camera / View
    m_Shader->SetUniformFloat3("uViewPosition", m_Camera->GetPosition());

    model->GetTexture()->Bind(0);
    m_Shader->SetUniformInt("textureSampler", 0);

    model->Draw();

    model->GetTexture()->Unbind();
}

}