#include "RenderPass.hpp"

#include "Engine/FrameBuffer.hpp"
#include "Engine/Shader.hpp"

namespace Atakama
{

RenderPass::RenderPass(Ref<RenderSystem> renderSystem)
: m_RenderSystem(renderSystem), m_FrameBuffer(FrameBuffer::Create())
{

}

void RenderPass::Draw()
{
}

void RenderPass::Render()
{
    // In the case when we want to render directly in the context
    // we should not use FrameBuffer
    if (m_FrameBuffer)
        m_FrameBuffer->Bind();

    Draw();

    if (m_FrameBuffer)
        m_FrameBuffer->Unbind();
}

Ref<FrameBuffer> RenderPass::GetFrameBuffer()
{
    return m_FrameBuffer;
}

void RenderPass::SetFrameBuffer(Ref<FrameBuffer> frameBuffer)
{
    ASSERT(frameBuffer != nullptr && "Cannot assign nullptr to a framebuffer");
    m_FrameBuffer = frameBuffer;
}

Ref<Texture> RenderPass::GetOutputColorTexture()
{
    return m_FrameBuffer->GetColorTexture();
}

Ref<Texture> RenderPass::GetOutputDepthTexture()
{
    return m_FrameBuffer->GetDepthTexture();
}

Ref<Texture> RenderPass::GetOutputMeshTexture()
{
    return m_FrameBuffer->GetMeshTexture();
}

void RenderPass::Resize(glm::uvec2 size)
{
    if (size == m_Size)
        return;

    if (size.x > 0.0f && size.y >0.0f)
    {
        m_FrameBuffer->Resize(size.x, size.y);
    }
}

glm::uvec2 RenderPass::GetSize()
{
    return m_Size;
}

void RenderPass::AddDependency(Ref<RenderPass> renderPass)
{
    m_Dependencies.push_back(renderPass);
}


void RenderPass::RemoveDependency(Ref<RenderPass> renderPass)
{
    m_Dependencies.erase(std::remove_if(m_Dependencies.begin(), m_Dependencies.end(), [&renderPass](Ref<RenderPass>& item){
        return item == renderPass;
    }));
}

//
// SceneRenderPass
//

SceneRenderPass::SceneRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene>& scene)
: RenderPass(renderSystem), m_Scene(scene)
{

}

}
