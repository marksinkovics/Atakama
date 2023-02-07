#include "SubMesh.hpp"
#include "Atakama/Scene/Components/TransformComponent.hpp"

namespace Atakama
{

bool SubMesh::Vertex::operator==(const Vertex &other) const
{
    return
        position == other.position &&
        color == other.color &&
        normal == other.normal &&
        uv == other.uv;
}

VertexBufferLayout SubMesh::Vertex::GetLayout()
{
    return {
        { VertexBufferElement::Type::Float3, "aPosition"},
        { VertexBufferElement::Type::Float2, "aUV"},
        { VertexBufferElement::Type::Float3, "aNormal"},
        { VertexBufferElement::Type::Float3, "aColor"},
    };
}

SubMesh::SubMesh(std::vector<Vertex>& vertices)
: m_Transform(CreateRef<TransformComponent>())
{
    m_VertexBuffer = VertexBuffer::Create((float*)vertices.data(), sizeof(Vertex) * vertices.size());
    m_VertexBuffer->SetLayout(SubMesh::Vertex::GetLayout());
    m_VertexArray = VertexArray::Create();
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
}

SubMesh::SubMesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
: m_Transform(CreateRef<TransformComponent>())
{
    m_VertexBuffer = VertexBuffer::Create((float*)vertices.data(), sizeof(Vertex) * vertices.size());
    m_VertexBuffer->SetLayout(SubMesh::Vertex::GetLayout());
    m_IndexBuffer = IndexBuffer::Create(indices.data(), indices.size());
    m_VertexArray = VertexArray::Create();
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);
}

SubMesh::~SubMesh()
{
}

//void SubMesh::Bind()
//{
//    m_VertexArray->Bind();
//}
//
//void SubMesh::Unbind()
//{
//    m_VertexArray->Unbind();
//}

glm::mat4 SubMesh::GetModelMatrix()
{
    return m_Transform->GetMat4();
}

glm::mat3 SubMesh::GetNormalMatrix()
{
    return m_Transform->GetInverseMat3();
}

Ref<TransformComponent> SubMesh::GetTransform()
{
    return m_Transform;
}

void SubMesh::SetTexture(Ref<Texture> texture)
{
    m_Texture = texture;
}

Ref<Texture> SubMesh::GetTexture()
{
    return m_Texture;
}

DrawingMode SubMesh::GetMode()
{
    return m_Mode;
}

void SubMesh::SetMode(DrawingMode mode)
{
    m_Mode = mode;
}

Ref<VertexArray>& SubMesh::GetVertexArray()
{
    return m_VertexArray;
}

}
