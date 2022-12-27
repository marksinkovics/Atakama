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
    virtual Ref<Texture> GetTexture() const;
private:
    uint32_t m_Id;
    uint32_t m_TextureId;
    uint32_t m_RenderBufferId;
    Ref<Texture> m_Texture;
};

}

#endif /* OpenGL3FrameBuffer_hpp */
