#include "ScreenRenderer.hpp"
#include "FileSystem.hpp"
#include "Events/WindowEvent.hpp"
#include "Events/EventDispatcher.hpp"
#include "Engine/AssetManager.hpp"
#include "Window.hpp"

namespace OGLSample
{

void ScreenRenderer::Init(Ref<RenderSystem> renderSystem, Ref<Camera> camera)
{
    Ref<Shader> shader = CreateRef<Shader>(FileSystem::GetShaderFile("screen_shader.vert"), FileSystem::GetShaderFile("screen_shader.frag"));
    Renderer::Init(renderSystem, camera, shader);
    
    m_QuadMesh = AssetManager::LoadQuad();
    
//    Ref<Window> window = g_RuntimeGlobalContext.m_Window;
    m_FrameBuffer = FrameBuffer::Create(100.f, 100.f);
//    m_QuadMesh->GetSubMeshes()[0]->SetTexture(m_FrameBuffer->GetColorTexture());
}

void ScreenRenderer::Resize(uint32_t width, uint32_t height)
{
    m_FrameBuffer->Resize(width, height);
//    m_QuadMesh->GetSubMeshes()[0]->SetTexture(m_FrameBuffer->GetColorTexture());
}

glm::uvec2 ScreenRenderer::GetSize()
{
    return { m_FrameBuffer->GetWidth(), m_FrameBuffer->GetHeight() };
}

void ScreenRenderer::StartRecord()
{
    m_FrameBuffer->Bind();
}

void ScreenRenderer::StopRecord()
{
    m_FrameBuffer->Unbind();
}

void ScreenRenderer::Draw()
{
//    m_QuadMesh->Draw(m_RenderSystem, m_Shader);
}

Ref<FrameBuffer>& ScreenRenderer::GetFrameBuffer()
{
    return m_FrameBuffer;
}

}
