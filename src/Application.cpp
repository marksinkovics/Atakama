#include "Application.hpp"
#include "Shader.hpp"
#include "Filesystem.hpp"

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

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);


    Shader simpleVertShader(FileSystem::GetShaderPath() / "simple_shader.vert", GL_VERTEX_SHADER);
    Shader simpleFragShader(FileSystem::GetShaderPath() / "simple_shader.frag", GL_FRAGMENT_SHADER);
    ShaderProgram simpleProgram(simpleVertShader, simpleFragShader);

    static const GLfloat g_vertex_buffer_data[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,
    };

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(simpleProgram.GetId());
        glEnableVertexAttribArray(0); 
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(m_Window->GetWindow());
        glfwPollEvents();

    }
    while(m_Window->shouldClose());

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
}

}
