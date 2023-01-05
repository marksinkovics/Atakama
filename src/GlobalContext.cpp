#include "GlobalContext.hpp"

#include "Application.hpp"
#include "Engine/Engine.hpp"
#include "Events/Event.hpp"
#include "Events/EventDispatcher.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/RenderSystem.hpp"
#include "Log/LogSystem.hpp"

namespace OGLSample
{

RuntimeGlobalContext g_RuntimeGlobalContext;

void RuntimeGlobalContext::Init()
{
    m_GraphicsAPI = GraphicsAPI::None;
    
    m_LogSystem = CreateRef<LogSystem>();
    m_Dispatcher = CreateRef<EventDispatcher>();

    m_InputSystem = CreateRef<InputSystem>();
    m_InputSystem->Init();
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
