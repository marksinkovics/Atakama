#include "LightingRenderer.hpp"
#include "FileSystem.hpp"

#include <glm/gtc/matrix_inverse.hpp>


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

void LightingRenderer::Draw(Ref<Mesh> mesh)
{
    m_Shader->SetUniformMat4("uView", m_Camera->GetViewMatrix());
    m_Shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());
    // Lights
    m_Shader->SetUniformFloat4("uLightPosition", m_LightPosition);
    m_Shader->SetUniformFloat4("uLightColor", m_LightColor);
    // Camera / View
    m_Shader->SetUniformFloat3("uViewPosition", m_Camera->GetPosition());

    mesh->Draw(m_Shader);
}

}