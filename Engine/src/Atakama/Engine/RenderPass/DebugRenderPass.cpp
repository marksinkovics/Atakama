#include "DebugRenderPass.hpp"
#include "Atakama/Engine/Renderer/SimpleRenderer.hpp"
#include "Atakama/Engine/Renderer/PointLightRenderer.hpp"
#include "Atakama/Engine/Scene.hpp"
#include "Atakama/Engine/Camera.hpp"
#include "Atakama/Engine/AssetManager.hpp"

namespace Atakama
{

DebugRenderPass::DebugRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene> scene, Ref<Camera>& camera)
: SceneRenderPass(renderSystem, scene), m_Camera(camera), m_AxisMesh(AssetManager::Get()->LoadAxis())
{
    m_SimpleRenderer = CreateRef<SimpleRenderer>(m_RenderSystem, m_Camera);
    m_BillboardRenderer = CreateRef<PointLightRenderer>(m_RenderSystem, m_Camera);
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
