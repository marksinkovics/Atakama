#include "Mesh.hpp"
#include "Shader.hpp"
#include "RenderSystem.hpp"

namespace Atakama
{

Mesh::Mesh()
: m_Transform(CreateRef<Transform>())
{
}

Mesh::Mesh(std::vector<Scope<SubMesh>>& subMeshes)
: m_SubMeshes(std::move(subMeshes)), m_Transform(CreateRef<Transform>())
{

}

glm::mat4 Mesh::GetModelMatrix()
{
    return m_Transform->GetMat4();
}


glm::mat3 Mesh::GetNormalMatrix()
{
    return m_Transform->GetInverseMat3();
}

Ref<Transform> Mesh::GetTransform()
{
    return m_Transform;
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
        glm::mat4 modelMatrix = m_Transform->GetMat4() * subMesh->m_Transform->GetMat4();
        shader->SetUniformMat4("uModel", modelMatrix);

        glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(modelMatrix));
        shader->SetUniformMat3("uNormalMatrix", normalMatrix);

        shader->SetUniformInt("u_MeshId", m_Id);

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
        
        renderSystem->Draw(subMesh->GetMode(), subMesh->GetVertexArray());
                
        if (texture != nullptr)
        {
            subMesh->GetTexture()->Unbind();
        }
    }
}

int Mesh::GetId() const
{
    return m_Id;
}

void Mesh::SetId(int id)
{
    m_Id = id;
    LOG_DEBUG("Mesh registered with id: {}", m_Id);
}

}
