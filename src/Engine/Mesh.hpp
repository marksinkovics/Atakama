#ifndef MESH_HPP
#define MESH_HPP

#include "SubMesh.hpp"

namespace OGLSample
{

class Shader;
class RenderSystem;

class Mesh
{
public:
    Mesh(uint32_t id);
    Mesh(uint32_t id, std::vector<Scope<SubMesh>>& subMeshes);
    ~Mesh() = default;

    glm::mat4 GetModelMatrix();
    void SetModelMatrix(glm::mat4 modelMatrix);
    glm::mat3 GetNormalMatrix();

    void Translate(glm::vec3 translate);
    void Rotate(float angle, glm::vec3 rotate);
    void Scale(glm::vec3 scale);
    
    std::vector<Scope<SubMesh>>& GetSubMeshes();
    void AddSubMesh(Scope<SubMesh> subMesh);

    void Draw(Ref<RenderSystem>& renderSystem, Ref<Shader>& shader);

    uint32_t GetId() const;
    void SetId(uint32_t id);

private:
    uint32_t m_Id;
    std::vector<Scope<SubMesh>> m_SubMeshes;
    glm::mat4 m_ModelMatrix {1.0f};
};


}

#endif
