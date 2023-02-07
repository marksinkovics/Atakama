#ifndef ATAKAMA_MESH_HPP
#define ATAKAMA_MESH_HPP

#include "SubMesh.hpp"
#include "Atakama/Scene/Components/TransformComponent.hpp"

namespace Atakama
{

class Shader;
class RenderSystem;

class Mesh
{
public:
    Mesh();
    Mesh(std::vector<Scope<SubMesh>>& subMeshes);
    ~Mesh() = default;

    glm::mat4 GetModelMatrix();
    glm::mat3 GetNormalMatrix();
    Ref<TransformComponent> GetTransform();

    std::vector<Scope<SubMesh>>& GetSubMeshes();
    void AddSubMesh(Scope<SubMesh> subMesh);

    void Draw(Ref<RenderSystem>& renderSystem, Ref<Shader>& shader);

    int GetId() const;
    void SetId(int id);
    
private:
    int m_Id {0};
    std::vector<Scope<SubMesh>> m_SubMeshes;
    Ref<TransformComponent> m_Transform;
};


}

#endif
