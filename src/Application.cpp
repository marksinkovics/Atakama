#include "Application.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace OGLSample {


Application::Application()
{
    m_Window = std::make_unique<Window>(Application::WIDTH, Application::HEIGHT, "OpenGL Tutorial");
}

Application::~Application()
{

}

void Application::run()
{
    do{
        glClear( GL_COLOR_BUFFER_BIT );

        // Draw nothing, see you in tutorial 2 !

        // Swap buffers
        glfwSwapBuffers(m_Window->GetWindow());
        glfwPollEvents();

    }
    while(m_Window->shouldClose());

}

}
