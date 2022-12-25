#ifndef SUBMESH_HPP
#define SUBMESH_HPP

#include "Engine/RenderSystem.hpp"
#include "Engine/Texture.hpp"

#include "Engine/VertexBuffer.hpp"
#include "Engine/IndexBuffer.hpp"
#include "Engine/VertexArray.hpp"

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

    void Bind();
    void Unbind();
    void Draw(Ref<RenderSystem>& renderSystem);

    // model = T * S * R
    glm::mat4 GetModelMatrix();
    void SetModelMatrix(glm::mat4 modelMatrix);

    glm::mat3 GetNormalMatrix();

    void SetTexture(Ref<Texture> texture);
    Ref<Texture> GetTexture();

    DrawingMode GetMode();
    void SetMode(DrawingMode mode);
private:
    DrawingMode m_Mode = DrawingMode::Triangles;

    Ref<Texture> m_Texture;
    
    glm::mat4 m_ModelMatrix {1.0f};

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
