#include "Application.hpp"

#include "Events/EventDispatcher.hpp"
#include "Engine/InputSystem.hpp"
#include "Events/Event.hpp"

#include <imgui.h>
#include <GLFW/glfw3.h>

namespace OGLSample {

Application::Application()
{
    g_RuntimeGlobalContext.m_GraphicsAPI = GraphicsAPI::OpenGL3;
    
    m_Window = CreateRef<Window>(1024, 768, "OpenGL Tutorial");
    m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    g_RuntimeGlobalContext.m_Window = m_Window;
    
    g_RuntimeGlobalContext.m_Dispatcher->subscribe<MouseButtonPressedEvent>(std::bind(&Application::OnMouseButtonPressed, this, std::placeholders::_1));
    
    m_Engine = CreateRef<Engine>();
    g_RuntimeGlobalContext.m_Engine = m_Engine;
}

Application::~Application()
{
    
}

void Application::OnEvent(Event &event)
{
    ImGuiIO& io = ImGui::GetIO();
    
    if (IsMouseEvent(event) && m_BlockEvents)
        event.Handled |= io.WantCaptureMouse;

    if (IsKeyboardEvent(event) && m_BlockEvents)
        event.Handled |= io.WantCaptureKeyboard;

    if (event.Handled)
        return;
    
    g_RuntimeGlobalContext.m_Dispatcher->post(event);
}

bool Application::OnMouseButtonPressed(MouseButtonPressedEvent &event)
{
    if (event.GetButton() == GLFW_MOUSE_BUTTON_MIDDLE)
    {
        Ref<InputSystem> inputSystem = g_RuntimeGlobalContext.m_InputSystem;
        inputSystem->SetFocusMode(!inputSystem->GetFocusMode());
    }
    
    return false;
}

void Application::BlockEvent(bool value)
{
    m_BlockEvents = value;
}

void Application::run()
{
    m_Engine->Init(m_Window);
    do
    {
        m_Engine->Run();
    }
    while(m_Window->ShouldClose());
    
    m_Engine->Shutdown();
}

}
