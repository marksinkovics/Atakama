#include "Application.hpp"
#include "Shader.hpp"
#include "FileSystem.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Input.hpp"

#include "Renderer/SimpleRenderer.hpp"
#include "Renderer/TextureRenderer.hpp"

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

    Ref<Shader> simpleProgram = CreateRef<Shader>(FileSystem::GetShaderFile("simple_shader.vert"), FileSystem::GetShaderFile("simple_shader.frag"));
    Ref<Shader> textureProgram = CreateRef<Shader>(FileSystem::GetShaderFile("texture_shader.vert"), FileSystem::GetShaderFile("texture_shader.frag"));

    Ref<Texture> texture1 = CreateRef<Texture>(FileSystem::GetTexturePath() / "uvtemplate.bmp");
    Ref<Texture> texture2 = CreateRef<Texture>(FileSystem::GetTexturePath() / "uvmap.png");
    Ref<Texture> vikingRoomTexture = CreateRef<Texture>(FileSystem::GetTexturePath() / "viking_room.png");

    Ref<Model> cubeModel = LoadOBJFile(FileSystem::GetModelPath() / "cube.obj");
    cubeModel->SetModelMatrix(glm::translate(cubeModel->GetModelMatrix(), {-2.f, 0, 0}));
    cubeModel->SetTexture(texture1);

    Ref<Model> triangleModel = LoadTriangle();
    triangleModel->SetModelMatrix(glm::translate(triangleModel->GetModelMatrix(), {0, 0, -1}));

    Ref<Model> cubeModel2 = LoadOBJFile(FileSystem::GetModelPath() / "cube.obj");
    assert(cubeModel2 && "Model didn't load");

    cubeModel2->SetModelMatrix(glm::translate(cubeModel2->GetModelMatrix(), {1.25, 0, -1}));
    cubeModel2->SetTexture(texture2);

    Ref<Model> vikingRoomModel = LoadOBJFile(FileSystem::GetModelPath() / "viking_room.obj");
    vikingRoomModel->SetTexture(vikingRoomTexture);
    vikingRoomModel->SetModelMatrix(glm::translate(vikingRoomModel->GetModelMatrix(), {0.f, -1.f, 1.5f}));
    vikingRoomModel->SetModelMatrix(glm::rotate(vikingRoomModel->GetModelMatrix(), glm::radians(90.0f), {0.f, 0.f, -1.f}));
    vikingRoomModel->SetModelMatrix(glm::rotate(vikingRoomModel->GetModelMatrix(), glm::radians(90.0f), {0.f, -1.f, 0.f}));

    Ref<Model> smoothVaseModel = LoadOBJFile(FileSystem::GetModelPath() / "smooth_vase.obj");

    Ref<Camera> camera = CreateRef<Camera>(m_Window);

    auto currentTime = std::chrono::high_resolution_clock::now();

    Ref<SimpleRenderer> simpleRenderer = CreateRef<SimpleRenderer>();
    simpleRenderer->Init(camera);

    Ref<TextureRenderer> textureRenderer = CreateRef<TextureRenderer>();
    textureRenderer->Init(camera);

    do {
        glfwPollEvents();

        auto newTime = std::chrono::high_resolution_clock::now();
        float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
        currentTime = newTime;

        camera->Update(frameTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        textureRenderer->Begin();
        // textureRenderer->Draw(cubeModel);
        // textureRenderer->Draw(cubeModel2);
        textureRenderer->Draw(vikingRoomModel);
        // textureRenderer->Draw(smoothVaseModel);
        textureRenderer->End();

        // simpleRenderer->Begin();
        // simpleRenderer->Draw(triangleModel);
        // simpleRenderer->End();

        // Swap buffers
        glfwSwapBuffers(m_Window->GetWindow());
        glfwPollEvents();

    }
    while(m_Window->ShouldClose());
}

}
