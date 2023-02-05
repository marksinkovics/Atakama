#ifndef ATAKAMA_APPLICATION_HPP
#define ATAKAMA_APPLICATION_HPP

#include "Atakama/Core/Window.hpp"
#include "Atakama/Events/Event.hpp"
#include "Atakama/Events/KeyEvent.hpp"
#include "Atakama/Events/MouseEvent.hpp"
#include "Atakama/Events/WindowEvent.hpp"

#include "Atakama/Engine/Engine.hpp"

#include "Atakama/Core/Layer.hpp"
#include "Atakama/ImGui/ImGuiLayer.hpp"

#include <stdint.h>

namespace Atakama
{

class Application
{
public:
    Application();
    ~Application();

    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;

    virtual void OnEvent(Event &event);

    virtual bool OnMouseButtonPressed(MouseButtonPressedEvent &event);
    virtual bool OnKeyPressed(KeyPressedEvent &event);
    virtual bool OnWindowClose(WindowCloseEvent &event);
    virtual bool OnWindowFrameBufferResize(WindowFrameBufferResizeEvent& event);

    virtual void BlockEvent(bool value);

    virtual void Run();

    virtual void AddLayer(Layer* layer);
    virtual void RemoveLayer(Layer* layer);

    virtual Ref<Engine> GetEngine();
    virtual Ref<Profiler> GetProfiler();
protected:
    Ref<Window> m_Window;
    Ref<Profiler> m_Profiler;
    Ref<Engine> m_Engine;
    bool m_BlockEvents;
    bool m_Running {true};

    LayerStack m_LayerStack;
    ImGuiLayer* m_ImGuiLayer;
};

}

#endif
