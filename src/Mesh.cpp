#include "Mesh.hpp"

#include <glm/gtc/matrix_inverse.hpp>


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

}