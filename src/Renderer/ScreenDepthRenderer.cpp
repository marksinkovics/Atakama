#include "ScreenDepthRenderer.hpp"
#include "FileSystem.hpp"
#include "Events/WindowEvent.hpp"
#include "Events/EventDispatcher.hpp"
#include "Engine/AssetManager.hpp"

namespace OGLSample
{

void ScreenDepthRenderer::Init(Ref<RenderSystem> renderSystem, Ref<Camera> camera)
{
    Ref<Shader> shader = CreateRef<Shader>(FileSystem::GetShaderFile("screen_depth_shader.vert"), FileSystem::GetShaderFile("screen_depth_shader.frag"));
    Renderer::Init(renderSystem, camera, shader);
    
    m_QuadMesh = AssetManager::LoadQuad();
    
    g_RuntimeGlobalContext.m_Dispatcher->subscribe<WindowFrameBufferResizeEvent>(std::bind(&ScreenDepthRenderer::OnWindowFrameBufferResize, this, std::placeholders::_1));

    Ref<Window> window = g_RuntimeGlobalContext.m_Window;
    m_FrameBuffer = FrameBuffer::Create(window->GetFrameBufferWidth(), window->GetFrameBufferHeight());
}

bool ScreenDepthRenderer::OnWindowFrameBufferResize(WindowFrameBufferResizeEvent& event)
{
    m_QuadMesh->GetSubMeshes()[0]->SetTexture(nullptr);
    m_FrameBuffer.reset();
    m_FrameBuffer = FrameBuffer::Create(event.GetWidth(), event.GetHeight());
    return false;
}

void ScreenDepthRenderer::StartRecord()
{
    m_FrameBuffer->Bind();
}

void ScreenDepthRenderer::StopRecord()
{
    m_FrameBuffer->Unbind();
}

void ScreenDepthRenderer::Draw(float time, glm::vec2 frameSize, Ref<Texture> depthTexture)
{
    m_QuadMesh->GetSubMeshes()[0]->SetTexture(depthTexture);
    m_Shader->SetUniformFloat("uTime", time);
    m_Shader->SetUniformFloat2("uFrameSize", frameSize);
    m_QuadMesh->Draw(m_RenderSystem, m_Shader);
}

Ref<FrameBuffer>& ScreenDepthRenderer::GetFrameBuffer()
{
    return m_FrameBuffer;
}

}
