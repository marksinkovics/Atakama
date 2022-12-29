#include "OpenGL3FrameBuffer.hpp"
#include "OpenGL3Texture.hpp"
#include "Window.hpp"
#include "Debug/OpenGL3/OpenGL3Debug.hpp"

namespace OGLSample
{

OpenGL3FrameBuffer::OpenGL3FrameBuffer(uint32_t width, uint32_t height)
: m_Width(width), m_Height(height)
{
    // Texture
    glGenTextures(1, &m_ColorTextureId);
    m_ColorTexture = CreateRef<OpenGL3Texture>(m_ColorTextureId);
    glBindTexture(GL_TEXTURE_2D, m_ColorTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

    glGenTextures(1, &m_DepthTextureId);
    m_DepthTexture = CreateRef<OpenGL3Texture>(m_DepthTextureId);
    glBindTexture(GL_TEXTURE_2D, m_DepthTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

    
    // Color render buffer
    glGenRenderbuffers(1, &m_RenderBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // Depth render buffer
    glGenRenderbuffers(1, &m_DepthRenderBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRenderBufferId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Width, m_Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthRenderBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    // Frame buffer
    glGenFramebuffers(1, &m_Id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
    // Attach the render buffer to the frame buffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorTextureId, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthTextureId, 0);


//    GLenum DrawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT};
//    glDrawBuffers(2, DrawBuffers);
    
    printFramebufferInfo(m_Id);
    if(!CheckFrameBufferStatus(m_Id))
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        LOG_FATAL("Failed to make complete framebuffer object");
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

OpenGL3FrameBuffer::~OpenGL3FrameBuffer()
{
    glDeleteFramebuffers(1, &m_Id);
    m_ColorTexture.reset();
    m_DepthTexture.reset();
    glDeleteRenderbuffers(1, &m_RenderBufferId);
}

void OpenGL3FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
}

void OpenGL3FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Ref<Texture> OpenGL3FrameBuffer::GetColorTexture() const
{
    return m_ColorTexture;
}

Ref<Texture> OpenGL3FrameBuffer::GetDepthTexture() const
{
    return m_DepthTexture;
}

int OpenGL3FrameBuffer::GetWidth() const
{
    return m_Width;
}

int OpenGL3FrameBuffer::GetHeight() const
{
    return m_Height;
}


}
