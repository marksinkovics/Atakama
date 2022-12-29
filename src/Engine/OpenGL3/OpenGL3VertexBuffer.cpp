#include "OpenGL3VertexBuffer.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OGLSample
{

OpenGL3VertexBuffer::OpenGL3VertexBuffer(size_t size)
: m_Size(size)
{
    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}
OpenGL3VertexBuffer::OpenGL3VertexBuffer(float* vertices, size_t size)
: m_Size(size)
{
    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGL3VertexBuffer::~OpenGL3VertexBuffer()
{
    glDeleteBuffers(1, &m_Id);
}

void OpenGL3VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}
void OpenGL3VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGL3VertexBuffer::SetData(const void* data, size_t size)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

size_t OpenGL3VertexBuffer::GetCount()
{
    return m_Size / m_Layout.GetStride();
}

VertexBufferLayout& OpenGL3VertexBuffer::GetLayout()
{
    return m_Layout;
}

void OpenGL3VertexBuffer::SetLayout(const VertexBufferLayout& layout)
{
    m_Layout = layout;
}

}
