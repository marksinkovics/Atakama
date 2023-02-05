#include "MainRenderPass.hpp"
#include "Atakama/Engine/RenderSystem.hpp"

#include "Atakama/Engine/Renderer/LightingRenderer.hpp"

#include "Atakama/Engine/Scene.hpp"
#include "Atakama/Engine/Camera.hpp"
//#include "Atakama/Engine/FrameBuffer.hpp"

namespace Atakama
{


MainRenderPass::MainRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene> scene, Ref<Camera>& camera)
: SceneRenderPass(renderSystem, scene), m_Camera(camera)
{
    m_Renderer = CreateRef<LightingRenderer>(m_RenderSystem, m_Camera);
}

void MainRenderPass::Draw()
{
    m_RenderSystem->SetDepthTest(true);
    m_RenderSystem->SetClearColor({0.0f, 0.0f, 0.4f, 0.0f});
    m_RenderSystem->Clear();

    m_Renderer->Begin(m_Scene->GetLight());
    for(const auto& mesh : *m_Scene)
    {
        m_Renderer->Draw(mesh);
    }
    m_Renderer->End();
}

std::string MainRenderPass::GetName()
{
    return "Main RenderPass";
}

}
