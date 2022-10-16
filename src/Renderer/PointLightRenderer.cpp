#include "PointLightRenderer.hpp"
#include "FileSystem.hpp"
#include "Model.hpp"
#include "ModelUtils.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace OGLSample
{

void PointLightRenderer::Init(Ref<Camera> camera)
{
    m_LightModel = LoadLightModel();
    Ref<Shader> shader = CreateRef<Shader>(FileSystem::GetShaderFile("point_light.vert"), FileSystem::GetShaderFile("point_light.frag"));
    Renderer::Init(camera, shader);

}

void PointLightRenderer::Draw(glm::vec4 lightPosition, glm::vec4 lightColor)
{
    glm::mat4 t = glm::translate(glm::mat4(1.0f), glm::vec3(lightPosition));

    m_Shader->SetUniformMat4("uModel", t);
    m_Shader->SetUniformMat4("uView", m_Camera->GetViewMatrix());
    m_Shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());
    // Lights
    m_Shader->SetUniformFloat4("uLightPosition", lightPosition);
    m_Shader->SetUniformFloat4("uLightColor", lightColor);
    // Camera / View
    m_Shader->SetUniformFloat3("uViewPosition", m_Camera->GetPosition());

    m_LightModel->Draw();
}

}
