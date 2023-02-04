#include "OpenGL3GraphicsContext.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Atakama
{

void OpenGL3GraphicsContext::Init()
{
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
}

void OpenGL3GraphicsContext::Register(void *window)
{
    if (!window)
    {
        LOG_FATAL("Registering OpenGL Graphics context failed.");
    }
    
    m_Window = static_cast<GLFWwindow*>(window);
    
    glfwMakeContextCurrent(m_Window); // Initialize GLEW
    SetVSync(true);

    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    if (GLEW_OK != error)
    {
        LOG_FATAL("glewInit Error: {}", (char*)glewGetErrorString(error));
    }
}

void OpenGL3GraphicsContext::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}

void OpenGL3GraphicsContext::SetVSync(bool enable)
{
    m_VSyncEnabled = enable;
    if (m_VSyncEnabled)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }
}

bool OpenGL3GraphicsContext::GetVSync() const
{
    return m_VSyncEnabled;
}

}
