#include "OpenGL3FrameBuffer.hpp"
#include "OpenGL3Texture.hpp"
#include "Window.hpp"

namespace OGLSample
{

OpenGL3FrameBuffer::OpenGL3FrameBuffer()
{
    Ref<Window> window = g_RuntimeGlobalContext.m_Window;
    m_Width = window->GetFrameBufferWidth();
    m_Height = window->GetFrameBufferHeight();
        
    // Frame buffer
    glGenFramebuffers(1, &m_Id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
        
    // Texture
    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureId, 0);
    m_Texture = CreateRef<OpenGL3Texture>(m_TextureId);

    // Render buffer
    glGenRenderbuffers(1, &m_RenderBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferId);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        LOG_FATAL("Failed to make complete framebuffer object {}", status);
    }
}

OpenGL3FrameBuffer::~OpenGL3FrameBuffer()
{
    glDeleteFramebuffers(1, &m_Id);
    m_Texture.reset();
    glDeleteRenderbuffers(1, &m_RenderBufferId);
}

void OpenGL3FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
//    glBindTexture(GL_TEXTURE_2D, m_TextureId);
//    glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferId);
}

void OpenGL3FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    glBindTexture(GL_TEXTURE_2D, 0);
//    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

Ref<Texture> OpenGL3FrameBuffer::GetTexture() const
{
    return m_Texture;
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
