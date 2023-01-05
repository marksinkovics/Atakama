#include "MainRenderPass.hpp"
#include "Engine/RenderSystem.hpp"

#include "Renderer/LightingRenderer.hpp"
#include "Renderer/SimpleRenderer.hpp"
#include "Renderer/PointLightRenderer.hpp"

#include "Engine/Scene.hpp"
#include "Engine/Camera.hpp"

#include "Engine/AssetManager.hpp"

namespace OGLSample
{


MainRenderPass::MainRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene> scene, Ref<Camera> camera)
: SceneRenderPass(renderSystem, scene), m_Camera(camera)
{
    m_Renderer = CreateRef<LightingRenderer>();
    m_Renderer->Init(m_RenderSystem, m_Camera);
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

DebugRenderPass::DebugRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene> scene, Ref<Camera> camera, Ref<FrameBuffer> frameBuffer)
: SceneRenderPass(renderSystem, scene), m_Camera(camera), m_AxisMesh(AssetManager::LoadAxis())
{
    m_FrameBuffer = frameBuffer;
    m_SimpleRenderer = CreateRef<SimpleRenderer>();
    m_SimpleRenderer->Init(m_RenderSystem, m_Camera);

    m_BillboardRenderer = CreateRef<PointLightRenderer>();
    m_BillboardRenderer->Init(m_RenderSystem, m_Camera);
}

void DebugRenderPass::Draw()
{
    m_SimpleRenderer->Begin();
    m_SimpleRenderer->Draw(m_AxisMesh);
    m_SimpleRenderer->End();

    m_BillboardRenderer->Begin();
    m_BillboardRenderer->Draw(m_Scene->GetLight());
    m_BillboardRenderer->End();
}

std::string DebugRenderPass::GetName()
{
    return "Debug RenderPass";
}


}
