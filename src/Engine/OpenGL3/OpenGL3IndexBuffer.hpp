#ifndef OPENGL3_INDEX_BUFFER_HPP
#define OPENGL3_INDEX_BUFFER_HPP

#include "Engine/IndexBuffer.hpp"

namespace OGLSample
{

class OpenGL3IndexBuffer: public IndexBuffer
{
public:
    OpenGL3IndexBuffer(uint32_t* indices, uint32_t count);
    virtual ~OpenGL3IndexBuffer();
    virtual void Bind() const;
    virtual void Unbind() const;
    virtual uint32_t GetCount() const;
private:
    uint32_t m_Id;
    uint32_t m_Count;
};

}

#endif
