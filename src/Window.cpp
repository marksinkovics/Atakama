#include "Window.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

#include <GL/glew.h>

namespace OGLSample
{

Window::Window(uint32_t width, uint32_t height, const std::string& name)
: m_Width(width), m_Height(height), m_Name(name)
{
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), NULL, NULL);
    glfwMakeContextCurrent(m_Window); // Initialize GLEW

    glewExperimental = true;
    glewInit();

    glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);

    glfwSetWindowUserPointer(m_Window, this);

    //resize
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        Window* handler = (Window*)glfwGetWindowUserPointer(window);
        if (!handler)
            return;
        
        handler->m_Width = width;
        handler->m_Height = height;

    });
    
    // window close
    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){

    });

    // key
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

    // mouse
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
    glfwSwapBuffers(m_Window);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

}
