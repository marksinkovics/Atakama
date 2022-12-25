#ifndef OPENGL3_VERTEX_BUFFER_HPP
#define OPENGL3_VERTEX_BUFFER_HPP

#include "Engine/VertexBufferLayout.hpp"
#include "Engine/VertexBuffer.hpp"

namespace OGLSample
{

class OpenGL3VertexBuffer: public VertexBuffer
{
public:
    OpenGL3VertexBuffer(uint32_t size);
    OpenGL3VertexBuffer(float* vertices, uint32_t size);
    
    virtual ~OpenGL3VertexBuffer();
    
    virtual void Bind() const;
    virtual void Unbind() const;
    
    virtual void SetData(const void* data, uint32_t size);
    
    virtual uint32_t GetCount();
    
    virtual VertexBufferLayout& GetLayout();
    virtual void SetLayout(const VertexBufferLayout& layout);
private:
    uint32_t m_Id;
    VertexBufferLayout m_Layout;
    uint32_t m_Size;
};

}

#endif
