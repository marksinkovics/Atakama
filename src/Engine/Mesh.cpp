#include "Mesh.hpp"
#include "Shader.hpp"

namespace OGLSample
{

Mesh::Mesh()
{

}

Mesh::Mesh(std::vector<Scope<SubMesh>>& subMeshes)
: m_SubMeshes(std::move(subMeshes)), m_ModelMatrix(glm::mat4(1.0f))
{

}

glm::mat4 Mesh::GetModelMatrix()
{
    return m_ModelMatrix;
}

void Mesh::SetModelMatrix(glm::mat4 modelMatrix)
{
    m_ModelMatrix = modelMatrix;
}

glm::mat3 Mesh::GetNormalMatrix()
{
    return glm::inverseTranspose(glm::mat3(m_ModelMatrix));
}

void Mesh::Translate(glm::vec3 translate)
{
    m_ModelMatrix = glm::translate(m_ModelMatrix, translate);
}

void Mesh::Rotate(float angle, glm::vec3 rotate)
{
    m_ModelMatrix = glm::rotate(m_ModelMatrix, angle, rotate);
}

void Mesh::Scale(glm::vec3 scale)
{
    m_ModelMatrix = glm::scale(m_ModelMatrix, scale);
}

std::vector<Scope<SubMesh>>& Mesh::GetSubMeshes()
{
    return m_SubMeshes;
}

void Mesh::AddSubMesh(Scope<SubMesh> subMesh)
{
    m_SubMeshes.push_back(std::move(subMesh));
}

void Mesh::Draw(Ref<RenderSystem>& renderSystem, Ref<Shader>& shader)
{
    for (auto& subMesh: m_SubMeshes)
    {
        glm::mat4 modelMatrix = m_ModelMatrix * subMesh->m_ModelMatrix;
        shader->SetUniformMat4("uModel", modelMatrix);

        glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(modelMatrix));
        shader->SetUniformMat3("uNormalMatrix", normalMatrix);

        auto texture = subMesh->GetTexture();
        if (texture == nullptr)
        {
            shader->SetUniformInt("uHasTexture", 0);
        }
        else
        {
            shader->SetUniformInt("uHasTexture", 1);
            subMesh->GetTexture()->Bind(0);
            shader->SetUniformInt("textureSampler", 0);
        }
        
        subMesh->Draw(renderSystem);
        
        if (texture != nullptr)
        {
            subMesh->GetTexture()->Unbind();
        }
    }
}

}
