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
    
    virtual void SetData(const void* data, size_t size) = 0;
    
    virtual size_t GetCount() = 0;
    
    virtual VertexBufferLayout& GetLayout() = 0;
    virtual void SetLayout(const VertexBufferLayout& layout) = 0;
    
    static Ref<VertexBuffer> Create(size_t size);
    static Ref<VertexBuffer> Create(float* vertices, size_t size);
};

}

#endif
