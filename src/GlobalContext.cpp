#include "GlobalContext.hpp"

#include "Events/Event.hpp"
#include "Events/EventDispatcher.hpp"
#include "Input.hpp"
#include "Render/RenderSystem.hpp"
#include "Log/LogSystem.hpp"

namespace OGLSample
{

RuntimeGlobalContext g_RuntimeGlobalContext;

void RuntimeGlobalContext::Init()
{
    m_LogSystem = CreateRef<LogSystem>();
    m_Dispatcher = CreateRef<EventDispatcher>();

    m_InputSystem = CreateRef<Input>();
    m_InputSystem->Init();
    
    m_RenderSystem = CreateRef<RenderSystem>();
}

void RuntimeGlobalContext::Shutdown()
{
    m_RenderSystem.reset();
    m_InputSystem.reset();
    m_Dispatcher.reset();
    m_LogSystem.reset();
}

}
