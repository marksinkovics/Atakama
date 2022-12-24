#include "SubMesh.hpp"

namespace OGLSample
{

bool SubMesh::Vertex::operator==(const Vertex &other) const
{
    return
        position == other.position &&
        color == other.color &&
        normal == other.normal &&
        uv == other.uv;
}

SubMesh::SubMesh(std::vector<Vertex>& vertices)
{
    m_VertexBuffer = CreateRef<VertexBuffer>((float*)vertices.data(), sizeof(Vertex) * vertices.size());
    m_VertexBuffer->SetLayout({
        { VertexBufferElement::Type::Float3, "aPosition"},
        { VertexBufferElement::Type::Float2, "aUV"},
        { VertexBufferElement::Type::Float3, "aNormal"},
        { VertexBufferElement::Type::Float3, "aColor"},
    });
    m_VertexArray = CreateRef<VertexArray>();
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
}

SubMesh::SubMesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    m_VertexBuffer = CreateRef<VertexBuffer>((float*)vertices.data(), sizeof(Vertex) * vertices.size());
    m_VertexBuffer->SetLayout({
        { VertexBufferElement::Type::Float3, "aPosition"},
        { VertexBufferElement::Type::Float2, "aUV"},
        { VertexBufferElement::Type::Float3, "aNormal"},
        { VertexBufferElement::Type::Float3, "aColor"},
    });
    m_IndexBuffer = CreateRef<IndexBuffer>(indices.data(), indices.size());
    m_VertexArray = CreateRef<VertexArray>();
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);
}

SubMesh::~SubMesh()
{
}

void SubMesh::Bind()
{
    m_VertexArray->Bind();
}

void SubMesh::Unbind()
{
    m_VertexArray->Unbind();
}

void SubMesh::Draw()
{
    m_VertexArray->Bind();
    
    if (m_VertexArray->GetIndexBuffer() && m_VertexArray->GetIndexBuffer()->GetCount() > 0)
    {
        glDrawElements(m_Type, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        glDrawArrays(m_Type, 0, m_VertexArray->GetVertexCount());
    }
    
    m_VertexArray->Unbind();
    
    return;
}

glm::mat4 SubMesh::GetModelMatrix()
{
    return m_ModelMatrix;
}

void SubMesh::SetModelMatrix(glm::mat4 modelMatrix)
{
    m_ModelMatrix = modelMatrix;
}

glm::mat3 SubMesh::GetNormalMatrix()
{
    return glm::inverseTranspose(glm::mat3(m_ModelMatrix));
}

void SubMesh::SetTexture(Ref<Texture> texture)
{
    m_Texture = texture;
}

Ref<Texture> SubMesh::GetTexture()
{
    return m_Texture;
}

GLuint SubMesh::GetType()
{
    return m_Type;
}

void SubMesh::SetType(GLuint type)
{
    m_Type = type;
}

}
