#include "ScreenRenderer.hpp"
#include "FileSystem.hpp"
#include "Events/WindowEvent.hpp"
#include "Events/EventDispatcher.hpp"
#include "Engine/AssetManager.hpp"

namespace OGLSample
{

void ScreenRenderer::Init(Ref<RenderSystem> renderSystem, Ref<Camera> camera)
{
    Ref<Shader> shader = Shader::Create(FileSystem::GetShaderFile("screen_shader.vert"), FileSystem::GetShaderFile("screen_shader.frag"));
    Renderer::Init(renderSystem, camera, shader);
    
    m_QuadMesh = AssetManager::LoadQuad();
    
    g_RuntimeGlobalContext.m_Dispatcher->subscribe<WindowFrameBufferResizeEvent>(std::bind(&ScreenRenderer::OnWindowFrameBufferResize, this, std::placeholders::_1));

    m_FrameBuffer = FrameBuffer::Create();
    m_QuadMesh->GetSubMeshes()[0]->SetTexture(m_FrameBuffer->GetTexture());
}

bool ScreenRenderer::OnWindowFrameBufferResize(WindowFrameBufferResizeEvent& event)
{
    m_QuadMesh->GetSubMeshes()[0]->SetTexture(nullptr);
    m_FrameBuffer.reset();
    m_FrameBuffer = FrameBuffer::Create();
    m_QuadMesh->GetSubMeshes()[0]->SetTexture(m_FrameBuffer->GetTexture());
    return false;
}

void ScreenRenderer::StartRecord()
{
    m_FrameBuffer->Bind();
}

void ScreenRenderer::StopRecord()
{
    m_FrameBuffer->Unbind();
}

void ScreenRenderer::Draw(float time, glm::vec2 frameSize)
{
    for (auto& subMesh: m_QuadMesh->GetSubMeshes())
    {
        m_Shader->SetUniformFloat("uTime", time);
        m_Shader->SetUniformFloat2("uFrameSize", frameSize);
        subMesh->SetTexture(m_FrameBuffer->GetTexture());
        subMesh->GetTexture()->Bind(0);
        m_Shader->SetUniformInt("textureSampler", 0);
        subMesh->Draw(m_RenderSystem);
        subMesh->GetTexture()->Unbind();
    }
}

}
