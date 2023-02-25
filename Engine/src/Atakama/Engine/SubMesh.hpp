#ifndef ATAKAMA_SUBMESH_HPP
#define ATAKAMA_SUBMESH_HPP

#include "Atakama/Engine/RenderTypes.hpp"
#include "Atakama/Engine/Texture.hpp"

#include "Atakama/Engine/Vertex.hpp"
#include "Atakama/Engine/VertexBuffer.hpp"
#include "Atakama/Engine/IndexBuffer.hpp"
#include "Atakama/Engine/VertexArray.hpp"

#include "Atakama/Scene/Components/TransformComponent.hpp"

namespace Atakama
{

class SubMesh
{
public:
    SubMesh(std::vector<Vertex>& vertices);
    SubMesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

    ~SubMesh();

    glm::mat4 GetModelMatrix();
    glm::mat3 GetNormalMatrix();
    Ref<TransformComponent> GetTransform();

    void SetTexture(Ref<Texture> texture);
    Ref<Texture> GetTexture();

    DrawingMode GetMode();
    void SetMode(DrawingMode mode);
    
    Ref<VertexArray>& GetVertexArray();
private:
    DrawingMode m_Mode = DrawingMode::Triangles;

    Ref<Texture> m_Texture;

    Ref<TransformComponent> m_Transform;

    Ref<VertexBuffer> m_VertexBuffer;
    Ref<IndexBuffer> m_IndexBuffer;
    Ref<VertexArray> m_VertexArray;

    friend class Mesh;
};

}

#endif
