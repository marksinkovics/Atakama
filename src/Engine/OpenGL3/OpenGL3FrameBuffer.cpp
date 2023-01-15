#include "OpenGL3FrameBuffer.hpp"
#include "OpenGL3Texture2D.hpp"
#include "Window.hpp"
#include "Debug/OpenGL3/OpenGL3Debug.hpp"

namespace OGLSample
{

static const uint32_t s_MaxFramebufferSize = 8192;

OpenGL3FrameBuffer::OpenGL3FrameBuffer()
{

}

OpenGL3FrameBuffer::OpenGL3FrameBuffer(uint32_t width, uint32_t height)
{
    Resize(width, height);
}

OpenGL3FrameBuffer::~OpenGL3FrameBuffer()
{
    glDeleteFramebuffers(1, &m_Id);
    m_ColorTexture.reset();
    m_MeshTexture.reset();
    m_DepthTexture.reset();
    glDeleteRenderbuffers(1, &m_ColorRenderBufferId);
}

void OpenGL3FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
    glViewport(0, 0, m_Width, m_Height);
    GLenum DrawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, DrawBuffers);
}

void OpenGL3FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Ref<Texture> OpenGL3FrameBuffer::GetColorTexture() const
{
    return m_ColorTexture;
}

Ref<Texture> OpenGL3FrameBuffer::GetMeshTexture() const
{
    return m_MeshTexture;
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

void OpenGL3FrameBuffer::Resize(int width, int height)
{
    if (width == m_Width && height == m_Height)
        return;

    if (width <= 0 || width > s_MaxFramebufferSize || height <= 0 || height > s_MaxFramebufferSize)
        return;

    if (m_Id)
    {
        glDeleteFramebuffers(1, &m_Id);
        m_ColorTexture.reset();
        m_MeshTexture.reset();
        m_DepthTexture.reset();
        glDeleteRenderbuffers(1, &m_DepthRenderBufferId);
        glDeleteRenderbuffers(1, &m_ColorRenderBufferId);
        glDeleteRenderbuffers(1, &m_MeshRenderBufferId);
    }

    m_Width = width;
    m_Height = height;

    // Texture
    m_ColorTexture = CreateRef<OpenGL3Texture2D>();
    glBindTexture(GL_TEXTURE_2D, m_ColorTexture->GetId());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Mesh
    m_MeshTexture = CreateRef<OpenGL3Texture2D>();
    glBindTexture(GL_TEXTURE_2D, m_MeshTexture->GetId());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, m_Width, m_Height, 0, GL_RED_INTEGER, GL_INT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Depth
    m_DepthTexture = CreateRef<OpenGL3Texture2D>();
    glBindTexture(GL_TEXTURE_2D, m_DepthTexture->GetId());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Color render buffer
    glGenRenderbuffers(1, &m_ColorRenderBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, m_ColorRenderBufferId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_ColorRenderBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // Mesh render buffer
    glGenRenderbuffers(1, &m_MeshRenderBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, m_MeshRenderBufferId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RED_INTEGER, m_Width, m_Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, m_MeshRenderBufferId);
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
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorTexture->GetId(), 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_MeshTexture->GetId(), 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthTexture->GetId(), 0);

//    printFramebufferInfo(m_Id);
    if(!CheckFrameBufferStatus(m_Id))
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        LOG_FATAL("Failed to make complete framebuffer object");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

int OpenGL3FrameBuffer::ReadInt(int index, int x, int y)
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Id);
    glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
    int value;
    glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &value);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    return value;
}

}
