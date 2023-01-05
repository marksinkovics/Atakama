#ifndef RUNTIME_GLOBAL_CONTEXT_HPP
#define RUNTIME_GLOBAL_CONTEXT_HPP

namespace OGLSample
{

class Application;
class Window;
class Engine;
class EventDispatcher;
class InputSystem;
class LogSystem;
enum class GraphicsAPI;

class RuntimeGlobalContext
{
public:
    void Init();
    void Shutdown();

    Ref<Application> m_Application;
    Ref<LogSystem> m_LogSystem;
    Ref<EventDispatcher> m_Dispatcher;
    Ref<InputSystem> m_InputSystem;
    
    Ref<Window> m_Window;
    Ref<Engine> m_Engine;
    
    GraphicsAPI m_GraphicsAPI;

    bool m_Editor { true };
};

extern bool IsEditor();

extern RuntimeGlobalContext g_RuntimeGlobalContext;

}

#endif
