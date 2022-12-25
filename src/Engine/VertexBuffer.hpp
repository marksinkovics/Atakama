#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include "VertexBufferLayout.hpp"

namespace OGLSample
{


class VertexBuffer
{
public:
    virtual ~VertexBuffer() = default;
    
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    
    virtual void SetData(const void* data, uint32_t size) = 0;
    
    virtual uint32_t GetCount() = 0;
    
    virtual VertexBufferLayout& GetLayout() = 0;
    virtual void SetLayout(const VertexBufferLayout& layout) = 0;
    
    static Ref<VertexBuffer> Create(uint32_t size);
    static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
};

}

#endif
