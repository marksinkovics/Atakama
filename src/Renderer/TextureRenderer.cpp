#include "TextureRenderer.hpp"
#include "FileSystem.hpp"

namespace OGLSample
{

void TextureRenderer::Init(Ref<Camera> camera)
{
    Ref<Shader> shader = CreateRef<Shader>(FileSystem::GetShaderFile("texture_shader.vert"), FileSystem::GetShaderFile("texture_shader.frag"));
    Renderer::Init(camera, shader);
}

void TextureRenderer::Draw(Ref<Mesh> mesh)
{
    m_Shader->SetUniformMat4("uView", m_Camera->GetViewMatrix());
    m_Shader->SetUniformMat4("uProjection", m_Camera->GetProjectionMatrix());

    for (auto& subMesh: mesh->GetSubMeshes())
    {
        glm::mat4 model = mesh->GetModelMatrix() * subMesh->GetModelMatrix();
        m_Shader->SetUniformMat4("uModel", model);
        subMesh->GetTexture()->Bind(0);
        m_Shader->SetUniformInt("textureSampler", 0);
        subMesh->Draw();
        subMesh->GetTexture()->Unbind();
    }

}

}