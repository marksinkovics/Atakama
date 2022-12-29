#include "OpenGL3IndexBuffer.hpp"

namespace OGLSample
{

OpenGL3IndexBuffer::OpenGL3IndexBuffer(uint32_t* indices, size_t count)
: m_Count(count)
{
    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGL3IndexBuffer::~OpenGL3IndexBuffer()
{
    glDeleteBuffers(1, &m_Id);
}

void OpenGL3IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
}

void OpenGL3IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

size_t OpenGL3IndexBuffer::GetCount() const
{
    return m_Count;
}


}
