#ifndef FRAME_BUFFER_HPP
#define FRAME_BUFFER_HPP

#include "Texture.hpp"

namespace OGLSample
{

class FrameBuffer
{
public:
    ~FrameBuffer() = default;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual Ref<Texture> GetTexture() const = 0;
    
    static Ref<FrameBuffer> Create();
};

}

#endif
