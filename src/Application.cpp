#include "Application.hpp"
#include "Shader.hpp"
#include "Filesystem.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

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
    m_Window = CreateRef<Window>(Application::WIDTH, Application::HEIGHT, "OpenGL Tutorial");
}

Application::~Application()
{

}

void Application::run()
{
    glfwPollEvents();
    glfwSetCursorPos(m_Window->GetWindow(), Application::WIDTH/2, Application::HEIGHT/2);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    Ref<Shader> simpleVertShader = CreateRef<Shader>(FileSystem::GetShaderPath() / "simple_shader.vert", GL_VERTEX_SHADER);
    Ref<Shader> simpleFragShader = CreateRef<Shader>(FileSystem::GetShaderPath() / "simple_shader.frag", GL_FRAGMENT_SHADER);
    Ref<ShaderProgram> simpleProgram = CreateRef<ShaderProgram>(simpleVertShader, simpleFragShader);

    Ref<Shader> textureVertShader = CreateRef<Shader>(FileSystem::GetShaderPath() / "texture_shader.vert", GL_VERTEX_SHADER);
    Ref<Shader> textureFragShader = CreateRef<Shader>(FileSystem::GetShaderPath() / "texture_shader.frag", GL_FRAGMENT_SHADER);
    Ref<ShaderProgram> textureProgram = CreateRef<ShaderProgram>(textureVertShader, textureFragShader);

    Ref<Texture> texture = CreateRef<Texture>(FileSystem::GetTexturePath() / "uvtemplate.bmp");

    Model cubeModel = LoadCubeModel();
    cubeModel.SetModelMatrix(glm::translate(cubeModel.GetModelMatrix(), {-1.25, 0, 0}));

    Model triangleModel = LoadTriangle();
    triangleModel.SetModelMatrix(glm::translate(triangleModel.GetModelMatrix(), {1.25, 0, -1}));

    Ref<Camera> camera = CreateRef<Camera>(m_Window);

    auto currentTime = std::chrono::high_resolution_clock::now();

    do {
        glfwPollEvents();

        auto newTime = std::chrono::high_resolution_clock::now();
        float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
        currentTime = newTime;

        camera->Update(frameTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        textureProgram->Bind();
        glm::mat4 cubeMVPMatrix = camera->GetProjectionMatrix() * camera->GetViewMatrix() * cubeModel.GetModelMatrix();
        textureProgram->SetUniformMat4("MVP", cubeMVPMatrix);
    	glBindTexture(GL_TEXTURE_2D, texture->GetId());
        textureProgram->SetUniformInt("textureSampler", 0);
        cubeModel.Draw();

        simpleProgram->Bind();
        glm::mat4 triangleMVPMatrix = camera->GetProjectionMatrix() * camera->GetViewMatrix() * triangleModel.GetModelMatrix();
        simpleProgram->SetUniformMat4("MVP", triangleMVPMatrix);
        triangleModel.Draw();

        // Swap buffers
        glfwSwapBuffers(m_Window->GetWindow());
        glfwPollEvents();

    }
    while(m_Window->ShouldClose());
}

}
