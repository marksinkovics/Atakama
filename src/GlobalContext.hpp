#ifndef RUNTIME_GLOBAL_CONTEXT_HPP
#define RUNTIME_GLOBAL_CONTEXT_HPP

namespace OGLSample
{

class Window;
class EventDispatcher;
class Input;
class RenderSystem;
class LogSystem;

class RuntimeGlobalContext
{
public:
    void Init();
    void Shutdown();

    Ref<Window> m_Window;
    Ref<EventDispatcher> m_Dispatcher;
    Ref<Input> m_InputSystem;
    Ref<RenderSystem> m_RenderSystem;
    Ref<LogSystem> m_LogSystem;
};

extern RuntimeGlobalContext g_RuntimeGlobalContext;

}

#endif
