#include "Application.hpp"

#include "Atakama/Events/EventDispatcher.hpp"
#include "Atakama/Core/InputSystem.hpp"
#include "Atakama/Events/Event.hpp"
#include "Atakama/Core/Profiler.hpp"

#include <imgui.h>
#include <GLFW/glfw3.h>

namespace Atakama {

Application::Application()
{
    g_RuntimeGlobalContext.m_Application = this;
    
    g_RuntimeGlobalContext.m_GraphicsAPI = GraphicsAPI::OpenGL3;
    
    m_Window = CreateRef<Window>(1024, 768, "Atakama Engine");
    m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    g_RuntimeGlobalContext.m_Window = m_Window;
    
    g_RuntimeGlobalContext.m_Dispatcher->subscribe<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
    g_RuntimeGlobalContext.m_Dispatcher->subscribe<WindowFrameBufferResizeEvent>(std::bind(&Application::OnWindowFrameBufferResize, this, std::placeholders::_1));

    m_Profiler = CreateRef<Profiler>();
    m_Engine = CreateRef<Engine>();
    g_RuntimeGlobalContext.m_Engine = m_Engine;
    m_Engine->Init(m_Window, m_Profiler);

    m_ImGuiLayer = new ImGuiLayer(m_Engine->m_RenderSystem, m_Window);
    AddLayer(m_ImGuiLayer);

    m_BlockEvents = !IsEditor();
}

Application::~Application()
{
    g_RuntimeGlobalContext.m_Application = nullptr;
}

void Application::OnEvent(Event &event)
{
    ImGuiIO& io = ImGui::GetIO();

    if (IsMouseEvent(event) && io.WantCaptureMouse && m_BlockEvents)
    {
        g_RuntimeGlobalContext.m_InputSystem->ClearMouseEvents();
        event.Handled = true;
    }

    if (IsKeyboardEvent(event) && io.WantCaptureKeyboard && m_BlockEvents)
    {
        g_RuntimeGlobalContext.m_InputSystem->ClearKeyboardEvents();
        event.Handled = true;
    }

    if (event.Handled)
        return;
    
    g_RuntimeGlobalContext.m_Dispatcher->post(event);
}

bool Application::OnWindowClose(WindowCloseEvent &event)
{
    m_Running = false;
    return false;
}

bool Application::OnWindowFrameBufferResize(WindowFrameBufferResizeEvent& event)
{
    m_Engine->UpdateRenderingViewportSize({event.GetWidth(), event.GetHeight()});
    return false;
}

void Application::BlockEvent(bool value)
{
    m_BlockEvents = value;
}

void Application::Run()
{
    while (m_Running)
    {
        float ts = m_Engine->CalculateDeltaTime();

        m_Engine->Run();

        for (Layer* layer : m_LayerStack)
        {
            layer->OnUpdate(ts);
        }

        m_ImGuiLayer->Begin();
        for (Layer* layer : m_LayerStack)
        {
            layer->OnUpdateUI(ts);
        }
        m_ImGuiLayer->End();

        g_RuntimeGlobalContext.m_InputSystem->Update(ts);

        m_Window->SwapBuffers();
        m_Window->PollEvents();
    }
    
    m_Engine->Shutdown();
}

void Application::AddLayer(Layer* layer)
{
    m_LayerStack.Add(layer);
}
void Application::RemoveLayer(Layer* layer)
{
    m_LayerStack.Remove(layer);
}

Ref<Engine> Application::GetEngine()
{
    return m_Engine;
}

Ref<Profiler> Application::GetProfiler()
{
    return m_Profiler;
}

}
