#ifndef RUNTIME_GLOBAL_CONTEXT_HPP
#define RUNTIME_GLOBAL_CONTEXT_HPP

namespace OGLSample
{

class Window;
class EventDispatcher;
class InputSystem;
class LogSystem;
enum class GraphicsAPI;

class RuntimeGlobalContext
{
public:
    void Init();
    void Shutdown();

    Ref<LogSystem> m_LogSystem;
    Ref<EventDispatcher> m_Dispatcher;
    Ref<InputSystem> m_InputSystem;
    
    Ref<Window> m_Window;
    
    GraphicsAPI m_GraphicsAPI;
};

extern RuntimeGlobalContext g_RuntimeGlobalContext;

}

#endif
