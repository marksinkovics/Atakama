#ifndef OPENGL3_FRAME_BUFFER
#define OPENGL3_FRAME_BUFFER

#include "Engine/FrameBuffer.hpp"
#include "Engine/Texture.hpp"

namespace OGLSample
{

class OpenGL3FrameBuffer: public FrameBuffer
{
public:
    OpenGL3FrameBuffer();
    virtual ~OpenGL3FrameBuffer();
    
    virtual void Bind() const;
    virtual void Unbind() const;
    virtual Ref<Texture> GetColorTexture() const;
    virtual Ref<Texture> GetDepthTexture() const;
    virtual int GetWidth() const;
    virtual int GetHeight() const;
private:
    uint32_t m_Id;
    
    uint32_t m_ColorTextureId;
    uint32_t m_DepthTextureId;
    
    uint32_t m_DepthRenderBufferId;
    uint32_t m_RenderBufferId;
    int m_Width;
    int m_Height;
    
    Ref<Texture> m_ColorTexture;
    Ref<Texture> m_DepthTexture;
};

}

#endif /* OpenGL3FrameBuffer_hpp */
