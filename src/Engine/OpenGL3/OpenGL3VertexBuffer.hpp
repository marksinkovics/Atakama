#ifndef ATAKAMA_OPENGL3_VERTEX_BUFFER_HPP
#define ATAKAMA_OPENGL3_VERTEX_BUFFER_HPP

#include "Engine/VertexBufferLayout.hpp"
#include "Engine/VertexBuffer.hpp"

namespace Atakama
{

class OpenGL3VertexBuffer: public VertexBuffer
{
public:
    OpenGL3VertexBuffer(size_t size);
    OpenGL3VertexBuffer(float* vertices, size_t size);
    
    virtual ~OpenGL3VertexBuffer();
    
    virtual void Bind() const;
    virtual void Unbind() const;
    
    virtual void SetData(const void* data, size_t size);
    
    virtual size_t GetCount();
    
    virtual VertexBufferLayout& GetLayout();
    virtual void SetLayout(const VertexBufferLayout& layout);
private:
    uint32_t m_Id;
    VertexBufferLayout m_Layout;
    size_t m_Size;
};

}

#endif
