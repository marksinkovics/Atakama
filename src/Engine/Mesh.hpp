#ifndef MESH_HPP
#define MESH_HPP

#include "SubMesh.hpp"
#include "Math/Transform.hpp"

namespace OGLSample
{

class Shader;
class RenderSystem;
class Transform;

class Mesh
{
public:
    Mesh();
    Mesh(std::vector<Scope<SubMesh>>& subMeshes);
    ~Mesh() = default;

    glm::mat4 GetModelMatrix();
    glm::mat3 GetNormalMatrix();
    Ref<Transform> GetTransform();

    std::vector<Scope<SubMesh>>& GetSubMeshes();
    void AddSubMesh(Scope<SubMesh> subMesh);

    void Draw(Ref<RenderSystem>& renderSystem, Ref<Shader>& shader);

    int GetId() const;
    void SetId(int id);
    
private:
    int m_Id {0};
    std::vector<Scope<SubMesh>> m_SubMeshes;
    Ref<Transform> m_Transform;
};


}

#endif
