#ifndef ATAKAMA_SUBMESH_HPP
#define ATAKAMA_SUBMESH_HPP

#include "Atakama/Engine/RenderTypes.hpp"
#include "Atakama/Engine/Texture.hpp"

#include "Atakama/Engine/VertexBuffer.hpp"
#include "Atakama/Engine/IndexBuffer.hpp"
#include "Atakama/Engine/VertexArray.hpp"

#include "Atakama/Scene/Components/TransformComponent.hpp"

namespace Atakama
{

class SubMesh
{
public:

    struct Vertex {
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;
        glm::vec3 color {1.0f, 1.0f, 1.0f};

        bool operator==(const Vertex &other) const;
        
        static VertexBufferLayout GetLayout();
    };

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

namespace std
{
    template<>
    struct hash<Atakama::SubMesh::Vertex>
    {
        size_t operator()(const Atakama::SubMesh::Vertex &vertex) const
        {
            size_t seed = 0;
            Atakama::hashCombine(seed, vertex.position, vertex.color, vertex.normal, vertex.uv);
            return seed;
        }
    };
}


#endif
