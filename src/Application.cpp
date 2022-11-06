#include "Application.hpp"
#include "Shader.hpp"
#include "FileSystem.hpp"
#include "SubMesh.hpp"
#include "AssetManager.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Perf/PerfMonitor.hpp"

#include "Renderer/SimpleRenderer.hpp"
#include "Renderer/TextureRenderer.hpp"
#include "Renderer/LightingRenderer.hpp"
#include "Renderer/PointLightRenderer.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <memory>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
    Ref<Texture> wallTexture = CreateRef<Texture>(FileSystem::GetTexturePath() / "wall.jpg");

    Ref<Mesh> cubeModel = AssetManager::LoadOBJFile(FileSystem::GetModelPath() / "cube.obj");
    assert(cubeModel && "Model didn't load");
    cubeModel->SetModelMatrix(glm::translate(cubeModel->GetModelMatrix(), {-2.f, 1.0, 0}));
    cubeModel->GetSubMeshes()[0]->SetTexture(texture1);

    Ref<Mesh> triangleModel = AssetManager::LoadTriangle();
    triangleModel->SetModelMatrix(glm::mat4(1.0f));
    assert(triangleModel && "Model didn't load");

    Ref<Mesh> cubeModel2 = AssetManager::LoadOBJFile(FileSystem::GetModelPath() / "cube.obj");
    assert(cubeModel2 && "Model didn't load");
    cubeModel2->SetModelMatrix(glm::translate(cubeModel2->GetModelMatrix(), {1.25, 1.0, -1}));
    cubeModel2->GetSubMeshes()[0]->SetTexture(texture2);

    Ref<Mesh> vikingRoomModel = AssetManager::LoadOBJFile(FileSystem::GetModelPath() / "viking_room.obj");
    assert(vikingRoomModel && "Model didn't load");
    vikingRoomModel->GetSubMeshes()[0]->SetTexture(vikingRoomTexture);
    vikingRoomModel->SetModelMatrix(glm::translate(vikingRoomModel->GetModelMatrix(), {0.f, -1.f, 1.5f}));
    vikingRoomModel->SetModelMatrix(glm::rotate(vikingRoomModel->GetModelMatrix(), glm::radians(90.0f), {0.f, 0.f, -1.f}));
    vikingRoomModel->SetModelMatrix(glm::rotate(vikingRoomModel->GetModelMatrix(), glm::radians(90.0f), {0.f, -1.f, 0.f}));

    Ref<Mesh> smoothVaseModel = AssetManager::LoadOBJFile(FileSystem::GetModelPath() / "smooth_vase.obj");
    smoothVaseModel->SetModelMatrix(glm::mat4(1.0f));
    assert(smoothVaseModel && "Model didn't load");

    Ref<Mesh> floorModel = AssetManager::LoadOBJFile(FileSystem::GetModelPath() / "quad.obj");
    assert(floorModel && "Model didn't load");
    // floorModel->SetTexture(wallTexture);
    floorModel->SetModelMatrix(glm::rotate(floorModel->GetModelMatrix(), glm::radians(180.0f), {0.f, 0.f, -1.f}));
    floorModel->SetModelMatrix(glm::scale(floorModel->GetModelMatrix(), {3.f, 1.f, 3.f}));
    floorModel->SetModelMatrix(glm::translate(floorModel->GetModelMatrix(), {0.f, 0.f, 0.f}));


//    Ref<Texture> suzanneTexture = CreateRef<Texture>(FileSystem::GetTexturePath() / "suzanne.png");
//    Ref<Mesh> suzanne = LoadOBJFile(FileSystem::GetModelPath() / "suzanne.obj");
//    suzanne->SetTexture(suzanneTexture);
//    suzanne->SetModelMatrix(glm::mat4(1.0));


    Ref<Camera> camera = CreateRef<Camera>(m_Window);
    camera->LookAt({5.0f, 5.f, 5.f});


    Ref<SimpleRenderer> simpleRenderer = CreateRef<SimpleRenderer>();
    simpleRenderer->Init(camera);

    Ref<TextureRenderer> textureRenderer = CreateRef<TextureRenderer>();
    textureRenderer->Init(camera);

    Ref<LightingRenderer> lightingRenderer = CreateRef<LightingRenderer>();
    lightingRenderer->Init(camera);

    Ref<PointLightRenderer> pointLightRenderer = CreateRef<PointLightRenderer>();
    pointLightRenderer->Init(camera);


    glm::vec4 lightPosition {4.f, 4.f, 4.f, 1.f};
    glm::vec4 lightColor {1.f, 1.f, 1.f, 1.f};

    Ref<Mesh> lightModel = AssetManager::LoadCube(glm::vec3(lightColor));
    lightModel->SetModelMatrix(glm::scale(lightModel->GetModelMatrix(), {0.2f, 0.2f, 0.2f}));
    lightModel->SetModelMatrix(glm::translate(lightModel->GetModelMatrix(), glm::vec3(lightPosition)));

    Ref<Mesh> axisModel = AssetManager::LoadAxis();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    PerfMonitor perfMonitor;

    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::time_point<std::chrono::high_resolution_clock> cpuStartTimer, cpuStopTimer;

    do {
        glfwPollEvents();

        auto newTime = std::chrono::high_resolution_clock::now();
        float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
        currentTime = newTime;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

//        ImGui::ShowDemoWindow();

        perfMonitor.StartCPUTimer();
        perfMonitor.StartGPUTimer();

        if (!io.WantCaptureMouse || !io.WantCaptureKeyboard)
        {
            camera->Update(frameTime);
        }

        lightingRenderer->Begin(lightPosition, lightColor);
        lightingRenderer->Draw(floorModel);
        lightingRenderer->Draw(cubeModel);
        lightingRenderer->Draw(cubeModel2);
    //    lightingRenderer->Draw(suzanne);
        lightingRenderer->End();

    //    textureRenderer->Begin();
    //    textureRenderer->Draw(cubeModel);
    //    textureRenderer->Draw(cubeModel2);
    //    textureRenderer->Draw(vikingRoomModel);
    //    textureRenderer->End();

        simpleRenderer->Begin();
        simpleRenderer->Draw(axisModel);
    //    simpleRenderer->Draw(lightModel);
    //    simpleRenderer->Draw(triangleModel);
    //    simpleRenderer->Draw(smoothVaseModel);
        simpleRenderer->End();

        pointLightRenderer->Begin();
        pointLightRenderer->Draw(lightPosition, lightColor);
        pointLightRenderer->End();

        perfMonitor.StopGPUTimer();
        perfMonitor.StopCPUTimer();

        ImGui::Begin("ImGui Window");
        ImGui::Text("CPU time: %f ms", perfMonitor.GetCPUTime());
        if (perfMonitor.GetGPUAvailable())
        {
            ImGui::Text("GPU time: %f ms", perfMonitor.GetGPUTime());
        }
        else
        {
            ImGui::Text("GPU time: not available");
        }
        ImGui::DragFloat3("Light position", (float*)&lightPosition, 0.01);
        ImGui::ColorEdit3("Light color", (float*)&lightColor);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(m_Window->GetWindow());
        glfwPollEvents();

    }
    while(m_Window->ShouldClose());

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

}

}
