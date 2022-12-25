#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "VertexBufferLayout.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace OGLSample
{

class VertexArray
{
public:
    virtual ~VertexArray() = default;
    
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
    
    virtual uint32_t GetVertexCount() = 0;
    
    virtual std::vector<Ref<VertexBuffer>>& GetVertexBuffers() = 0;
    virtual Ref<IndexBuffer> GetIndexBuffer() = 0;
    
    static Ref<VertexArray> Create();
};

}

#endif
