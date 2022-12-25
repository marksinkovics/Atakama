#include "VertexBuffer.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OGLSample
{

VertexBuffer::VertexBuffer(uint32_t size)
: m_Size(size)
{
    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}
VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
: m_Size(size)
{
    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_Id);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}
void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, uint32_t size)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

uint32_t VertexBuffer::GetCount()
{
    return m_Size / m_Layout.GetStride();
}

VertexBufferLayout& VertexBuffer::GetLayout()
{
    return m_Layout;
}

void VertexBuffer::SetLayout(const VertexBufferLayout& layout)
{
    m_Layout = layout;
}

IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
: m_Count(count)
{
    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_Id);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t IndexBuffer::GetCount() const
{
    return m_Count;
}


VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_Id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_Id);
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_Id);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{
    Bind();
    vertexBuffer->Bind();
    const auto& layout = vertexBuffer->GetLayout();
    for (const auto& element: layout)
    {
        switch (element.Type)
        {
            case VertexBufferElement::Type::Float:
            case VertexBufferElement::Type::Float2:
            case VertexBufferElement::Type::Float3:
            case VertexBufferElement::Type::Float4:
            {
                glEnableVertexAttribArray(m_VertexBufferIndex);
                glVertexAttribPointer(
                  m_VertexBufferIndex,
                  element.GetComponentCount(element.Type),
                  element.GetOpenGLBaseType(element.Type),
                  element.Normalized ? GL_TRUE : GL_FALSE,
                  layout.GetStride(),
                  (void*)element.Offset
                );
                m_VertexBufferIndex++;
                break;
            }
            case VertexBufferElement::Type::Mat3:
            case VertexBufferElement::Type::Mat4:
            {
                const uint32_t count = element.GetComponentCount(element.Type);
                for (uint32_t i = 0; i < count; i++)
                {
                    glEnableVertexAttribArray(m_VertexBufferIndex);
                    glVertexAttribPointer(
                      m_VertexBufferIndex,
                      count,
                      element.GetOpenGLBaseType(element.Type),
                      element.Normalized ? GL_TRUE : GL_FALSE,
                      layout.GetStride(),
                      (const void*)(element.Offset + sizeof(float) * count * i)
                    );
                    glVertexAttribDivisor(m_VertexBufferIndex, 1);
                    m_VertexBufferIndex++;
                }
                break;
            }
            case VertexBufferElement::Type::Int:
            case VertexBufferElement::Type::Int2:
            case VertexBufferElement::Type::Int3:
            case VertexBufferElement::Type::Int4:
            case VertexBufferElement::Type::Bool:
            {
                glEnableVertexAttribArray(m_VertexBufferIndex);
                glVertexAttribIPointer(
                  m_VertexBufferIndex,
                  element.GetComponentCount(element.Type),
                  element.GetOpenGLBaseType(element.Type),
                  layout.GetStride(),
                  (const void*)element.Offset
                );
                m_VertexBufferIndex++;
                break;
            }
            case VertexBufferElement::Type::None:
            {
                assert(false && "Unknown element type");
            }
                
        }
    }
    m_VertexBuffers.push_back(vertexBuffer);
    Unbind();
}

void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
    Bind();
    indexBuffer->Bind();
    m_IndexBuffer = indexBuffer;
    Unbind();
}

std::vector<Ref<VertexBuffer>>& VertexArray::GetVertexBuffers()
{
    return m_VertexBuffers;
}

Ref<IndexBuffer> VertexArray::GetIndexBuffer()
{
    return m_IndexBuffer;
}

uint32_t VertexArray::GetVertexCount()
{
    uint32_t count = 0;
    for (const auto& vertexBuffer : m_VertexBuffers)
    {
        count += vertexBuffer->GetCount();
    }
    return count;
}

}
