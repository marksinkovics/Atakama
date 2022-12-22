#ifndef RUNTIME_GLOBAL_CONTEXT_HPP
#define RUNTIME_GLOBAL_CONTEXT_HPP

namespace OGLSample
{

class Window;
class EventDispatcher;
class Input;

class RuntimeGlobalContext
{
public:
    void Init();

    Ref<Window> m_Window;
    Ref<EventDispatcher> m_Dispatcher;
    Ref<Input> m_InputSystem;
};

extern RuntimeGlobalContext g_RuntimeGlobalContext;

}

#endif