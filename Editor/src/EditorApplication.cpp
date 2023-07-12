#include "EditorApplication.hpp"

#include "Layer/MenuBarLayer.hpp"
#include "Layer/EditorLayer.hpp"
#include "Layer/StatsLayer.hpp"
#include "Layer/ViewportLayer.hpp"
#include "Layer/DepthViewLayer.hpp"
#include "Layer/SceneLayer.hpp"

#include <Atakama/Engine/RenderPass/MainRenderPass.hpp>
#include <Atakama/Engine/RenderPass/ViewportRenderPass.hpp>
#include <Atakama/Engine/RenderPass/OutlineRenderPass.hpp>
#include <Atakama/Asset/AssetManager.hpp>

#include "Atakama/Events/EventDispatcher.hpp"
#include <Atakama/Events/DropEvent.hpp>

namespace Atakama::Editor
{

EditorApplication::EditorApplication()
: Application()
{
    AddLayer(new EditorLayer());
    AddLayer(new MenuBarLayer());
    AddLayer(new StatsLayer());
    AddLayer(new ViewportLayer());
    AddLayer(new DepthViewLayer());
    AddLayer(new SceneLayer());

    m_Engine->GetViewportRenderPass()->RemoveDependency(m_Engine->GetMainRenderPass());
    m_Engine->GetViewportRenderPass()->AddDependency(m_Engine->GetOutlineRenderPass());
    m_Engine->GetViewportRenderPass()->SetEnable(false);

    g_RuntimeGlobalContext.m_Dispatcher->subscribe<DropEvent>(std::bind(&EditorApplication::OnDrop, this, std::placeholders::_1));
}

bool EditorApplication::OnDrop(DropEvent& event)
{

    for (auto&& path : event.GetPaths()) 
    {
        LOG_DEBUG("Editor - PATH: {}", path);

        g_RuntimeGlobalContext.m_AssetManager->ImportModel(path);
        g_RuntimeGlobalContext.m_Engine->GetScene()->AddModeById(path.filename().string());

    }
    return false;
}

}
