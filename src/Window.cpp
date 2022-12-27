#include "Window.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/WindowEvent.hpp"

#include "Platform/OpenGL3/OpenGL3GraphicsContext.hpp"

#include <GLFW/glfw3.h>

namespace OGLSample
{

Window::Window(uint32_t width, uint32_t height, const std::string& name)
: m_Width(width), m_Height(height), m_Name(name)
{
    if(!glfwInit())
    {
        LOG_FATAL("Failed to initialize GLFW");
    }
    
    m_GraphicsContext = GraphicsContext::Create();
    m_GraphicsContext->Init();

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), NULL, NULL); // Present it in a window

    m_GraphicsContext->Register(m_Window);
    
    glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetWindowUserPointer(m_Window, this);

    //resize
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        Window* handler = (Window*)glfwGetWindowUserPointer(window);
        if (!handler)
            return;
        
        handler->m_Width = width;
        handler->m_Height = height;

        WindowResizeEvent event(width, height);
        handler->m_EventCallback(event);
    });
    
    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
        Window* handler = (Window*)glfwGetWindowUserPointer(window);
        if (!handler)
            return;
        
        WindowCloseEvent event;
        handler->m_EventCallback(event);
    });
    
    glfwGetFramebufferSize(m_Window, (int*)&m_FrameBufferWidth, (int*)&m_FrameBufferHeight);
    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        Window* handler = (Window*)glfwGetWindowUserPointer(window);
        if (!handler)
            return;
        
        handler->m_FrameBufferWidth = width;
        handler->m_FrameBufferHeight = height;

        WindowFrameBufferResizeEvent event(width, height);
        handler->m_EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        Window* handler = (Window*)glfwGetWindowUserPointer(window);
        if (!handler)
            return;
        
        if (action == GLFW_PRESS) {
            KeyPressedEvent event(key, false);
            handler->m_EventCallback(event);
            return;
        }

        if (action == GLFW_RELEASE) {
            KeyReleasedEvent event(key, false);
            handler->m_EventCallback(event);
            return;
        }

        if (action == GLFW_REPEAT) {
            KeyPressedEvent event(key, true);
            handler->m_EventCallback(event);
            return;
        }
    });

    glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode){
        Window* handler = (Window*)glfwGetWindowUserPointer(window);
        if (!handler)
            return;
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods){
        Window* handler = (Window*)glfwGetWindowUserPointer(window);
        if (!handler)
            return;
        
        if (action == GLFW_PRESS) {
            MouseButtonPressedEvent event(button);
            handler->m_EventCallback(event);
            return;
        }

        if (action == GLFW_RELEASE) {
            MouseButtonReleasedEvent event(button);
            handler->m_EventCallback(event);
            return;
        }
    });
    
    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset){
        Window* handler = (Window*)glfwGetWindowUserPointer(window);
        if (!handler)
            return;

        MouseScrolledEvent event(xOffset, yOffset);
        handler->m_EventCallback(event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos){
        Window* handler = (Window*)glfwGetWindowUserPointer(window);
        if (!handler)
            return;
        
        MouseMovedEvent event(xPos, yPos);
        handler->m_EventCallback(event);
    });
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool Window::ShouldClose()
{
    return glfwGetKey(m_Window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(m_Window) == 0;
}

GLFWwindow* Window::GetWindow() const
{
    return m_Window;
}

float Window::GetWidth()
{
    return m_Width;
}

float Window::GetHeight()
{
    return m_Height;
}

float Window::GetFrameBufferWidth()
{
    return m_FrameBufferWidth;
}

float Window::GetFrameBufferHeight()
{
    return m_FrameBufferHeight;
}

glm::vec2 Window::GetSize()
{
    return { m_Width,  m_Height };
}

float Window::GetRatio()
{
    return (float)(m_Width / m_Height);
}

void Window::SetEventCallback(const EventCallbackFunc& callback)
{
    m_EventCallback = callback;
}

void Window::SwapBuffers()
{
    m_GraphicsContext->SwapBuffers();
}

void Window::PollEvents()
{
    glfwPollEvents();
}

}
