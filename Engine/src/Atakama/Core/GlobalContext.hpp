#ifndef ATAKAMA_RUNTIME_GLOBAL_CONTEXT_HPP
#define ATAKAMA_RUNTIME_GLOBAL_CONTEXT_HPP

namespace Atakama
{

class Application;
class Window;
class Engine;
class EventDispatcher;
class InputSystem;
class LogSystem;
enum class GraphicsAPI;
class AssetManager;

class RuntimeGlobalContext
{
public:
    void Init();
    void Shutdown();

    Application* m_Application;
    
    Ref<LogSystem> m_LogSystem;
    Ref<EventDispatcher> m_Dispatcher;
    Ref<InputSystem> m_InputSystem;
    
    Ref<Window> m_Window;
    Ref<Engine> m_Engine;
    
    GraphicsAPI m_GraphicsAPI;

    Ref<AssetManager> m_AssetManager;

    bool m_Editor { true };
};

extern bool IsEditor();

extern RuntimeGlobalContext g_RuntimeGlobalContext;

}

#endif
