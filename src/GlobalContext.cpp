#include "GlobalContext.hpp"

#include "Events/Event.hpp"
#include "Events/EventDispatcher.hpp"
#include "Input.hpp"

#include "Render/RenderSystem.hpp"

namespace OGLSample
{

RuntimeGlobalContext g_RuntimeGlobalContext;

void RuntimeGlobalContext::Init()
{
    m_Dispatcher = CreateRef<EventDispatcher>();

    m_InputSystem = CreateRef<Input>();
    m_InputSystem->Init();
    
    m_RenderSystem = CreateRef<RenderSystem>();
}

}
