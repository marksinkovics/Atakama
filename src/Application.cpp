#include "Application.hpp"
#include "Shader.hpp"
#include "Filesystem.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Input.hpp"

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

    Input::EnableDragging(m_Window, true);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    Ref<ShaderProgram> simpleProgram = CreateRef<ShaderProgram>(FileSystem::GetShaderPath() / "simple_shader.vert", FileSystem::GetShaderPath() / "simple_shader.frag");
    Ref<ShaderProgram> textureProgram = CreateRef<ShaderProgram>(FileSystem::GetShaderPath() / "texture_shader.vert", FileSystem::GetShaderPath() / "texture_shader.frag");

    Ref<Texture> texture1 = CreateRef<Texture>(FileSystem::GetTexturePath() / "uvtemplate.bmp");
    Ref<Texture> texture2 = CreateRef<Texture>(FileSystem::GetTexturePath() / "wall.jpg");

    Ref<Model> cubeModel = LoadCubeModel();
    cubeModel->SetModelMatrix(glm::translate(cubeModel->GetModelMatrix(), {-2.f, 0, 0}));

    Ref<Model> triangleModel = LoadTriangle();
    triangleModel->SetModelMatrix(glm::translate(triangleModel->GetModelMatrix(), {0, 0, -1}));

    Ref<Model> cubeModel2 = LoadOBJFile(FileSystem::GetModelPath() / "cube.obj");
    assert(cubeModel2 && "Model didn't load");

    cubeModel2->SetModelMatrix(glm::translate(cubeModel2->GetModelMatrix(), {1.25, 0, -1}));

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
        glm::mat4 cubeMVPMatrix = camera->GetProjectionMatrix() * camera->GetViewMatrix() * cubeModel->GetModelMatrix();
        textureProgram->SetUniformMat4("MVP", cubeMVPMatrix);
        texture1->Bind(0);
        textureProgram->SetUniformInt("textureSampler", 0);
        cubeModel->Draw();
        textureProgram->Unbind();
        texture1->Unbind();

        simpleProgram->Bind();
        glm::mat4 triangleMVPMatrix = camera->GetProjectionMatrix() * camera->GetViewMatrix() * triangleModel->GetModelMatrix();
        simpleProgram->SetUniformMat4("MVP", triangleMVPMatrix);
        triangleModel->Draw();
        simpleProgram->Unbind();

        textureProgram->Bind();
        glm::mat4 cube2MVPMatrix = camera->GetProjectionMatrix() * camera->GetViewMatrix() * cubeModel2->GetModelMatrix();
        textureProgram->SetUniformMat4("MVP", cube2MVPMatrix);
        texture2->Bind(1);
        textureProgram->SetUniformInt("textureSampler", 1);
        cubeModel2->Draw();
        textureProgram->Unbind();
        texture2->Unbind();


        // Swap buffers
        glfwSwapBuffers(m_Window->GetWindow());
        glfwPollEvents();

    }
    while(m_Window->ShouldClose());
}

}
