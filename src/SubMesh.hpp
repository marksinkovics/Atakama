#ifndef MODEL_HPP
#define MODEL_HPP

#include "Texture.hpp"
#include "Render/VertexBuffer.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
    };

    SubMesh(std::vector<Vertex>& vertices);
    SubMesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

    ~SubMesh();

    void Bind();
    void Unbind();
    void Draw();

    // model = T * S * R
    glm::mat4 GetModelMatrix();
    void SetModelMatrix(glm::mat4 modelMatrix);

    glm::mat3 GetNormalMatrix();

    void SetTexture(Ref<Texture> texture);
    Ref<Texture> GetTexture();

    GLuint GetType();
    void SetType(GLuint type);
private:
    void GenerateVertexArray();
private:
    GLuint m_Type = GL_TRIANGLES;

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
