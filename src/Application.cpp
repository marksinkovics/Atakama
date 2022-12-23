#include "Application.hpp"
#include "Shader.hpp"
#include "FileSystem.hpp"
#include "SubMesh.hpp"
#include "AssetManager.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Perf/PerfMonitor.hpp"
#include "Events/Event.hpp"

#include "Renderer/SimpleRenderer.hpp"
#include "Renderer/TextureRenderer.hpp"
#include "Renderer/LightingRenderer.hpp"
#include "Renderer/PointLightRenderer.hpp"


#include <stdio.h>
#include <stdlib.h>
#include <memory>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OGLSample {

Application::Application()
{
    m_Window = CreateRef<Window>(Application::WIDTH, Application::HEIGHT, "OpenGL Tutorial");
    m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    g_RuntimeGlobalContext.m_Window = m_Window;
    
    g_RuntimeGlobalContext.m_Dispatcher->subscribe<MouseButtonPressedEvent>(EventType::MouseButtonPressed, std::bind(&Application::OnMouseButtonPressed, this, std::placeholders::_1));
    
    m_Engine = CreateRef<Engine>();
}

Application::~Application()
{

}

void Application::OnEvent(Event &event)
{
    ImGuiIO& io = ImGui::GetIO();
    
    if (IsMouseEvent(event))
        event.Handled |= io.WantCaptureMouse;

    if (IsKeyboardEvent(event))
        event.Handled |= io.WantCaptureKeyboard;

    if (event.Handled)
        return;
    
    g_RuntimeGlobalContext.m_Dispatcher->post(event);
}

bool Application::OnMouseButtonPressed(MouseButtonPressedEvent &event)
{
    if (event.GetButton() == GLFW_MOUSE_BUTTON_MIDDLE)
    {
        Ref<Input> inputSystem = g_RuntimeGlobalContext.m_InputSystem;
        inputSystem->SetFocusMode(!inputSystem->GetFocusMode());
    }
    
    return false;
}

void Application::run()
{
    m_Engine->Init(m_Window);
    do {
        m_Engine->Run();
    } while(m_Window->ShouldClose());
    m_Engine->Shutdown();
}

}
