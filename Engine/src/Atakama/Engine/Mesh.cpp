#include "Mesh.hpp"

namespace Atakama
{

Mesh::Mesh(std::vector<Vertex>& vertices)
{
    m_VertexBuffer = VertexBuffer::Create((float*)vertices.data(), sizeof(Vertex) * vertices.size());
    m_VertexBuffer->SetLayout(Vertex::GetLayout());
    m_VertexArray = VertexArray::Create();
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    m_VertexBuffer = VertexBuffer::Create((float*)vertices.data(), sizeof(Vertex) * vertices.size());
    m_VertexBuffer->SetLayout(Vertex::GetLayout());
    m_IndexBuffer = IndexBuffer::Create(indices.data(), indices.size());
    m_VertexArray = VertexArray::Create();
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);
}

Mesh::~Mesh()
{
}

DrawingMode Mesh::GetMode()
{
    return m_Mode;
}

void Mesh::SetMode(DrawingMode mode)
{
    m_Mode = mode;
}

std::string Mesh::GetTextureId()
{
    return m_TextureId;
}

void Mesh::SetTextureId(const std::string& textureId)
{
    m_TextureId = textureId;
}

bool Mesh::HasTextureId()
{
    return !m_TextureId.empty();
}

Ref<VertexArray>& Mesh::GetVertexArray()
{
    return m_VertexArray;
}

}
