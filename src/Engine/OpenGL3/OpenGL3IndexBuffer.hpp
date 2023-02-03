#ifndef ATAKAMA_OPENGL3_INDEX_BUFFER_HPP
#define ATAKAMA_OPENGL3_INDEX_BUFFER_HPP

#include "Engine/IndexBuffer.hpp"

namespace Atakama
{

class OpenGL3IndexBuffer: public IndexBuffer
{
public:
    OpenGL3IndexBuffer(uint32_t* indices, size_t count);
    virtual ~OpenGL3IndexBuffer();
    virtual void Bind() const;
    virtual void Unbind() const;
    virtual size_t GetCount() const;
private:
    uint32_t m_Id;
    size_t m_Count;
};

}

#endif
