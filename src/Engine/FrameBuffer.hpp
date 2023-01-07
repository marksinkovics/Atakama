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
    virtual Ref<Texture> GetColorTexture() const = 0;
    virtual Ref<Texture> GetDepthTexture() const = 0;
    virtual Ref<Texture> GetMeshTexture() const = 0;
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
    virtual void Resize(int width, int height) = 0;

    virtual int ReadInt(int index, int x, int y) = 0;

    static Ref<FrameBuffer> Create();
    static Ref<FrameBuffer> Create(uint32_t width, uint32_t height);
};

}

#endif
