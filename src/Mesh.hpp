#ifndef MESH_HPP
#define MESH_HPP

#include "SubMesh.hpp"

namespace OGLSample
{

class Mesh
{
public:
    Mesh();
    Mesh(std::vector<Scope<SubMesh>>& subMeshes);
    ~Mesh() = default;

    glm::mat4 GetModelMatrix();
    void SetModelMatrix(glm::mat4 modelMatrix);
    glm::mat3 GetNormalMatrix();

    std::vector<Scope<SubMesh>>& GetSubMeshes();
    void AddSubMesh(Scope<SubMesh> subMesh);

private:
    std::vector<Scope<SubMesh>> m_SubMeshes;
    glm::mat4 m_ModelMatrix {1.0f};
};


}

#endif