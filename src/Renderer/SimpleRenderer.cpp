#include "SimpleRenderer.hpp"
#include "FileSystem.hpp"

namespace OGLSample
{

void SimpleRenderer::Init(Ref<Camera> camera)
{
    Ref<Shader> shader = CreateRef<Shader>(FileSystem::GetShaderFile("simple_shader.vert"), FileSystem::GetShaderFile("simple_shader.frag"));
    Renderer::Init(camera, shader);
}

void SimpleRenderer::Draw(Ref<Mesh> mesh)
{
    m_Shader->SetUniformMat4("uView", m_Camera->GetViewMatrix());
    m_Shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());

    for (auto& subMesh: mesh->GetSubMeshes())
    {
        glm::mat4 model = mesh->GetModelMatrix() * subMesh->GetModelMatrix();
        m_Shader->SetUniformMat4("uModel", model);
        subMesh->Draw();
    }
}

}