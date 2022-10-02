#include "Window.hpp"

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
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool Window::shouldClose()
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

float Window::GetRatio()
{
    return (float)(m_Width / m_Height);
}

}
