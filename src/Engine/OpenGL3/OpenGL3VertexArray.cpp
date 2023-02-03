#include "OpenGL3VertexArray.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Atakama
{

GLenum GetOpenGLBaseType(enum VertexBufferElement::Type type)
{
    switch (type)
    {
        case VertexBufferElement::Type::Float:   return GL_FLOAT;
        case VertexBufferElement::Type::Float2:  return GL_FLOAT;
        case VertexBufferElement::Type::Float3:  return GL_FLOAT;
        case VertexBufferElement::Type::Float4:  return GL_FLOAT;
        case VertexBufferElement::Type::Mat3:    return GL_FLOAT;
        case VertexBufferElement::Type::Mat4:    return GL_FLOAT;
        case VertexBufferElement::Type::Int:     return GL_INT;
        case VertexBufferElement::Type::Int2:    return GL_INT;
        case VertexBufferElement::Type::Int3:    return GL_INT;
        case VertexBufferElement::Type::Int4:    return GL_INT;
        case VertexBufferElement::Type::Bool:    return GL_BOOL;
        case VertexBufferElement::Type::None:    return 0;
    }
}

OpenGL3VertexArray::OpenGL3VertexArray()
{
    glGenVertexArrays(1, &m_Id);
}

OpenGL3VertexArray::~OpenGL3VertexArray()
{
    glDeleteVertexArrays(1, &m_Id);
}

void OpenGL3VertexArray::Bind() const
{
    glBindVertexArray(m_Id);
}

void OpenGL3VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void OpenGL3VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
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
                  GetOpenGLBaseType(element.Type),
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
                      GetOpenGLBaseType(element.Type),
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
                  GetOpenGLBaseType(element.Type),
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

void OpenGL3VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
    Bind();
    indexBuffer->Bind();
    m_IndexBuffer = indexBuffer;
    Unbind();
}

std::vector<Ref<VertexBuffer>>& OpenGL3VertexArray::GetVertexBuffers()
{
    return m_VertexBuffers;
}

Ref<IndexBuffer> OpenGL3VertexArray::GetIndexBuffer()
{
    return m_IndexBuffer;
}

uint32_t OpenGL3VertexArray::GetVertexCount()
{
    uint32_t count = 0;
    for (const auto& vertexBuffer : m_VertexBuffers)
    {
        count += vertexBuffer->GetCount();
    }
    return count;
}


}
