#include "ScreenDepthRenderer.hpp"
#include "FileSystem.hpp"
#include "Events/WindowEvent.hpp"
#include "Events/EventDispatcher.hpp"
#include "Engine/AssetManager.hpp"
#include "Window.hpp"


namespace OGLSample
{

void ScreenDepthRenderer::Init(Ref<RenderSystem> renderSystem, Ref<Camera> camera)
{
    Ref<Shader> shader = CreateRef<Shader>(FileSystem::GetShaderFile("screen_depth_shader.vert"), FileSystem::GetShaderFile("screen_depth_shader.frag"));
    Renderer::Init(renderSystem, camera, shader);
    
    m_QuadMesh = AssetManager::LoadQuad();
    
    Ref<Window> window = g_RuntimeGlobalContext.m_Window;
    m_FrameBuffer = FrameBuffer::Create(window->GetFrameBufferWidth(), window->GetFrameBufferHeight());
}

void ScreenDepthRenderer::Resize(uint32_t width, uint32_t height)
{
    m_QuadMesh->GetSubMeshes()[0]->SetTexture(nullptr);
    m_FrameBuffer->Resize(width, height);
}

glm::uvec2 ScreenDepthRenderer::GetSize()
{
    return { m_FrameBuffer->GetWidth(), m_FrameBuffer->GetHeight() };
}

void ScreenDepthRenderer::StartRecord()
{
    m_FrameBuffer->Bind();
}

void ScreenDepthRenderer::StopRecord()
{
    m_FrameBuffer->Unbind();
}

void ScreenDepthRenderer::Draw(Ref<Texture> depthTexture)
{
    m_QuadMesh->GetSubMeshes()[0]->SetTexture(depthTexture);
    m_QuadMesh->Draw(m_RenderSystem, m_Shader);
}

Ref<FrameBuffer>& ScreenDepthRenderer::GetFrameBuffer()
{
    return m_FrameBuffer;
}

}
