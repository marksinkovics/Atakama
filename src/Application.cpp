#include "Application.hpp"
#include "Shader.hpp"
#include "Filesystem.hpp"
#include "Model.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    Shader simpleVertShader(FileSystem::GetShaderPath() / "simple_shader.vert", GL_VERTEX_SHADER);
    Shader simpleFragShader(FileSystem::GetShaderPath() / "simple_shader.frag", GL_FRAGMENT_SHADER);
    ShaderProgram simpleProgram(simpleVertShader, simpleFragShader);

    glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)m_Window->GetRatio(), 0.1f, 100.0f);
    glm::mat4 ViewMatrix = glm::lookAt(
        glm::vec3(4, 3, 3), // Camera is in World Space
        glm::vec3(0, 0, 0), // looks at the origin
        glm::vec3(0, 1, 0) // Head is up
    );


    GLuint MatrixID = glGetUniformLocation(simpleProgram.GetId(), "MVP");

    Model cubeModel = LoadCubeModel();
    cubeModel.setModelMatrix(glm::translate(cubeModel.getModelMatrix(), {-1.25, 0, 0}));
    glm::mat4 cubeMVPMatrix = ProjectionMatrix * ViewMatrix * cubeModel.getModelMatrix();
    Model triangleModel = LoadTriangle();
    triangleModel.setModelMatrix(glm::translate(triangleModel.getModelMatrix(), {1.25, 0, -1}));
    glm::mat4 triangleMVPMatrix = ProjectionMatrix * ViewMatrix * triangleModel.getModelMatrix();

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        simpleProgram.use();

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &cubeMVPMatrix[0][0]);
        cubeModel.draw();

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangleMVPMatrix[0][0]);
        triangleModel.draw();

        // Swap buffers
        glfwSwapBuffers(m_Window->GetWindow());
        glfwPollEvents();

    }
    while(m_Window->shouldClose());
}

}
