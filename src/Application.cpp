#include "Application.hpp"
#include "Shader.hpp"
#include "Filesystem.hpp"
#include "Model.hpp"
#include "Texture.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <memory>

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

    Ref<Shader> simpleVertShader = CreateRef<Shader>(FileSystem::GetShaderPath() / "simple_shader.vert", GL_VERTEX_SHADER);
    Ref<Shader> simpleFragShader = CreateRef<Shader>(FileSystem::GetShaderPath() / "simple_shader.frag", GL_FRAGMENT_SHADER);
    Ref<ShaderProgram> simpleProgram = CreateRef<ShaderProgram>(simpleVertShader, simpleFragShader);

    Ref<Shader> textureVertShader = CreateRef<Shader>(FileSystem::GetShaderPath() / "texture_shader.vert", GL_VERTEX_SHADER);
    Ref<Shader> textureFragShader = CreateRef<Shader>(FileSystem::GetShaderPath() / "texture_shader.frag", GL_FRAGMENT_SHADER);
    Ref<ShaderProgram> textureProgram = CreateRef<ShaderProgram>(textureVertShader, textureFragShader);

    Ref<Texture> texture = CreateRef<Texture>(FileSystem::GetTexturePath() / "uvtemplate.bmp");

    glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)m_Window->GetRatio(), 0.1f, 100.0f);
    glm::mat4 ViewMatrix = glm::lookAt(
        glm::vec3(4, 3, 3), // Camera is in World Space
        glm::vec3(0, 0, 0), // looks at the origin
        glm::vec3(0, 1, 0) // Head is up
    );

    Model cubeModel = LoadCubeModel();
    cubeModel.SetModelMatrix(glm::translate(cubeModel.GetModelMatrix(), {-1.25, 0, 0}));
    glm::mat4 cubeMVPMatrix = ProjectionMatrix * ViewMatrix * cubeModel.GetModelMatrix();

    Model triangleModel = LoadTriangle();
    triangleModel.SetModelMatrix(glm::translate(triangleModel.GetModelMatrix(), {1.25, 0, -1}));
    glm::mat4 triangleMVPMatrix = ProjectionMatrix * ViewMatrix * triangleModel.GetModelMatrix();

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        textureProgram->Bind();
        textureProgram->SetUniformMat4("MVP", cubeMVPMatrix);
    	glBindTexture(GL_TEXTURE_2D, texture->GetId());
        textureProgram->SetUniformInt("textureSampler", 0);
        cubeModel.Draw();

        simpleProgram->Bind();
        simpleProgram->SetUniformMat4("MVP", triangleMVPMatrix);
        triangleModel.Draw();

        // Swap buffers
        glfwSwapBuffers(m_Window->GetWindow());
        glfwPollEvents();

    }
    while(m_Window->ShouldClose());
}

}
