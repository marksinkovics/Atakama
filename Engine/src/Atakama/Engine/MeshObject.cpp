#include "MeshObject.hpp"

namespace Atakama
{

MeshObject::MeshObject(std::vector<Vertex>& vertices)
{
    m_VertexBuffer = VertexBuffer::Create((float*)vertices.data(), sizeof(Vertex) * vertices.size());
    m_VertexBuffer->SetLayout(Vertex::GetLayout());
    m_VertexArray = VertexArray::Create();
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
}

MeshObject::MeshObject(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    m_VertexBuffer = VertexBuffer::Create((float*)vertices.data(), sizeof(Vertex) * vertices.size());
    m_VertexBuffer->SetLayout(Vertex::GetLayout());
    m_IndexBuffer = IndexBuffer::Create(indices.data(), indices.size());
    m_VertexArray = VertexArray::Create();
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);
}

MeshObject::~MeshObject()
{
}

DrawingMode MeshObject::GetMode()
{
    return m_Mode;
}

void MeshObject::SetMode(DrawingMode mode)
{
    m_Mode = mode;
}

Ref<VertexArray>& MeshObject::GetVertexArray()
{
    return m_VertexArray;
}

}
