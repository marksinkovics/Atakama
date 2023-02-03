#ifndef ATAKAMA_OPENGL3_VERTEX_ARRAY_HPP
#define ATAKAMA_OPENGL3_VERTEX_ARRAY_HPP

#include "Engine/VertexBufferLayout.hpp"
#include "Engine/VertexBuffer.hpp"
#include "Engine/IndexBuffer.hpp"
#include "Engine/VertexArray.hpp"

namespace Atakama
{

class OpenGL3VertexArray: public VertexArray
{
public:
    OpenGL3VertexArray();
    virtual ~OpenGL3VertexArray();
    virtual void Bind() const;
    virtual void Unbind() const;

    virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);
    
    virtual uint32_t GetVertexCount();
    
    virtual std::vector<Ref<VertexBuffer>>& GetVertexBuffers();
    virtual Ref<IndexBuffer> GetIndexBuffer();
private:
    uint32_t m_Id;
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;
    Ref<IndexBuffer> m_IndexBuffer;
    uint32_t m_VertexBufferIndex;
};

}

#endif
