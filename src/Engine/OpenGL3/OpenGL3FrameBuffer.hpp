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
    OpenGL3FrameBuffer(uint32_t width, uint32_t height);
    virtual ~OpenGL3FrameBuffer();
    
    virtual void Bind() const override;
    virtual void Unbind() const override;
    virtual Ref<Texture> GetColorTexture() const override;
    virtual Ref<Texture> GetDepthTexture() const override;
    virtual Ref<Texture> GetMeshTexture() const override;
    virtual int GetWidth() const override;
    virtual int GetHeight() const override;
    virtual void Resize(int width, int height) override;
    virtual int ReadInt(int index, int x, int y) override;
private:
    uint32_t m_Id;
        
    uint32_t m_DepthRenderBufferId;
    uint32_t m_ColorRenderBufferId;
    uint32_t m_MeshRenderBufferId;
    uint32_t m_Width;
    uint32_t m_Height;
    
    Ref<Texture> m_ColorTexture;
    Ref<Texture> m_DepthTexture;
    Ref<Texture> m_MeshTexture;
};

}

#endif /* OpenGL3FrameBuffer_hpp */
