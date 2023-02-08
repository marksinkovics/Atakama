#include "EditorApplication.hpp"

#include "Layer/MenuBarLayer.hpp"
#include "Layer/StatsLayer.hpp"
#include "Layer/ViewportLayer.hpp"
#include "Layer/DepthViewLayer.hpp"
#include "Layer/SceneLayer.hpp"

#include <Atakama/Engine/RenderPass/MainRenderPass.hpp>
#include <Atakama/Engine/RenderPass/ViewportRenderPass.hpp>
#include <Atakama/Engine/RenderPass/OutlineRenderPass.hpp>

namespace Atakama::Editor
{

EditorApplication::EditorApplication()
: Application()
{
    AddLayer(new MenuBarLayer());
    AddLayer(new StatsLayer());
    AddLayer(new ViewportLayer());
    AddLayer(new DepthViewLayer());
    AddLayer(new SceneLayer());

    m_Engine->GetViewportRenderPass()->RemoveDependency(m_Engine->GetMainRenderPass());
    m_Engine->GetViewportRenderPass()->AddDependency(m_Engine->GetOutlineRenderPass());
    m_Engine->GetViewportRenderPass()->SetEnable(false);
}



}
