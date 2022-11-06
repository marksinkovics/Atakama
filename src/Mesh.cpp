#include "Mesh.hpp"
#include "Shader.hpp"

namespace OGLSample
{

Mesh::Mesh()
{

}

Mesh::Mesh(std::vector<Scope<SubMesh>>& subMeshes)
    : m_SubMeshes(std::move(subMeshes))
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

std::vector<Scope<SubMesh>>& Mesh::GetSubMeshes()
{
    return m_SubMeshes;
}

void Mesh::AddSubMesh(Scope<SubMesh> subMesh)
{
    m_SubMeshes.push_back(std::move(subMesh));
}

void Mesh::Draw(Ref<Shader>& shader)
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

        subMesh->Draw();

        if (texture != nullptr)
        {
            subMesh->GetTexture()->Unbind();
        }
    }
}

}