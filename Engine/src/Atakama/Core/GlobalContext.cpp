#include "GlobalContext.hpp"

#include "Application.hpp"
#include "Atakama/Engine/Engine.hpp"
#include "Atakama/Events/Event.hpp"
#include "Atakama/Events/EventDispatcher.hpp"
#include "Atakama/Core/InputSystem.hpp"
#include "Atakama/Engine/RenderSystem.hpp"
#include "Atakama/Engine/AssetManager.hpp"
#include "Atakama/Engine/CameraSystem.hpp"

namespace Atakama
{

RuntimeGlobalContext g_RuntimeGlobalContext;

void RuntimeGlobalContext::Init()
{
    m_GraphicsAPI = GraphicsAPI::None;
    
    m_LogSystem = CreateRef<LogSystem>();
    m_Dispatcher = CreateRef<EventDispatcher>();

    m_InputSystem = CreateRef<InputSystem>();
    m_InputSystem->Init();

    m_AssetManager = CreateRef<AssetManager>();

    m_CameraSystem = CreateRef<CameraSystem>();
}

void RuntimeGlobalContext::Shutdown()
{
    m_InputSystem.reset();
    m_Dispatcher.reset();
    m_LogSystem.reset();
}

bool IsEditor()
{
    return g_RuntimeGlobalContext.m_Editor;
}

}
