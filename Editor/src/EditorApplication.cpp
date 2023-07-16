#include "EditorApplication.hpp"

#include "Layer/MenuBarLayer.hpp"
#include "Layer/EditorLayer.hpp"
#include "Layer/DocumentLayer.hpp"
#include "Layer/ProjectSettingsLayer.hpp"
#include "Layer/EditorConfigLayer.hpp"

#include "Layer/StatsLayer.hpp"
#include "Layer/ViewportLayer.hpp"
#include "Layer/DepthViewLayer.hpp"
#include "Layer/SceneLayer.hpp"
#include "Layer/TestLayer.hpp"

#include <Atakama/Engine/RenderPass/MainRenderPass.hpp>
#include <Atakama/Engine/RenderPass/ViewportRenderPass.hpp>
#include <Atakama/Engine/RenderPass/OutlineRenderPass.hpp>
#include <Atakama/Asset/AssetManager.hpp>

#include "Atakama/Events/EventDispatcher.hpp"
#include <Atakama/Events/DropEvent.hpp>

// Reminder: remove the imgui.ini file from the Debug folder, otherwise it will crash
#define TEST_LAYER 0

namespace Atakama::Editor
{

EditorApplication::EditorApplication()
    : Application(), m_WindowConfigs(g_RuntimeEditorContext.WindowConfigs)
{
    AddLayer(new MenuBarLayer());
#if TEST_LAYER
    AddLayer(new TestLayer());
#else
    AddLayer(new EditorLayer());
    AddLayer(new DocumentLayer());
    AddLayer(new ProjectSettingsLayer());
    AddLayer(new EditorConfigLayer());

    AddLayer(new StatsLayer());
    AddLayer(new ViewportLayer());
    AddLayer(new DepthViewLayer());
    AddLayer(new SceneLayer());
#endif

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
