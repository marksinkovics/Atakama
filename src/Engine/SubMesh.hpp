#ifndef SUBMESH_HPP
#define SUBMESH_HPP

#include "Engine/RenderTypes.hpp"
#include "Engine/Texture.hpp"

#include "Engine/VertexBuffer.hpp"
#include "Engine/IndexBuffer.hpp"
#include "Engine/VertexArray.hpp"

#include "Math/Transform.hpp"

namespace OGLSample
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
    Ref<Transform> GetTransform();

    void SetTexture(Ref<Texture> texture);
    Ref<Texture> GetTexture();

    DrawingMode GetMode();
    void SetMode(DrawingMode mode);
    
    Ref<VertexArray>& GetVertexArray();
private:
    DrawingMode m_Mode = DrawingMode::Triangles;

    Ref<Texture> m_Texture;

    Ref<Transform> m_Transform;

    Ref<VertexBuffer> m_VertexBuffer;
    Ref<IndexBuffer> m_IndexBuffer;
    Ref<VertexArray> m_VertexArray;

    friend class Mesh;
};

}

namespace std
{
    template<>
    struct hash<OGLSample::SubMesh::Vertex>
    {
        size_t operator()(const OGLSample::SubMesh::Vertex &vertex) const
        {
            size_t seed = 0;
            OGLSample::hashCombine(seed, vertex.position, vertex.color, vertex.normal, vertex.uv);
            return seed;
        }
    };
}


#endif
