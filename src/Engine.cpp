#include "Engine.hpp"

#include "Window.hpp"
#include "FileSystem.hpp"
#include "AssetManager.hpp"
#include "Input.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace OGLSample
{

void Engine::Init(Ref<Window>& window)
{
    m_Window = window;
    
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
    
    m_Camera = CreateRef<Camera>();
    m_Camera->LookAt({5.0f, 5.f, 5.f});
        
    m_Scene = CreateRef<SandboxScene>();
    m_Scene->Init();

    simpleRenderer = CreateRef<SimpleRenderer>();
    simpleRenderer->Init(m_Camera);

    textureRenderer = CreateRef<TextureRenderer>();
    textureRenderer->Init(m_Camera);

    lightingRenderer = CreateRef<LightingRenderer>();
    lightingRenderer->Init(m_Camera);

    pointLightRenderer = CreateRef<PointLightRenderer>();
    pointLightRenderer->Init(m_Camera);
            
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Engine::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Engine::CalculateDeltaTime()
{
    auto timePoint = std::chrono::high_resolution_clock::now();
    m_FrameTime = std::chrono::duration<float, std::chrono::seconds::period>(timePoint - m_LastTime).count();
    m_LastTime = timePoint;
}

void Engine::Run()
{
    CalculateDeltaTime();
    
    m_Camera->UpdateFrameTime(m_FrameTime);
    m_Camera->Update(m_FrameTime);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    perfMonitor.StartCPUTimer();
    perfMonitor.StartGPUTimer();
    
    lightingRenderer->Begin(m_Scene->GetLight());
    lightingRenderer->Draw(m_Scene->GetModelById("floor"));
    lightingRenderer->Draw(m_Scene->GetModelById("cube"));
    lightingRenderer->Draw(m_Scene->GetModelById("cube2"));
    lightingRenderer->Draw(m_Scene->GetModelById("vikingRoom"));
    lightingRenderer->End();
    
    simpleRenderer->Begin();
    simpleRenderer->Draw(m_Scene->GetModelById("axis"));
    simpleRenderer->End();

    pointLightRenderer->Begin();
    pointLightRenderer->Draw(m_Scene->GetLight());
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
    ImGui::DragFloat3("Light position", (float*)&m_Scene->GetLight()->GetPositionRef(), 0.01);
    ImGui::ColorEdit3("Light color", (float*)&m_Scene->GetLight()->GetColorRef());
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    g_RuntimeGlobalContext.m_InputSystem->Clear();
    m_Window->SwapBuffers();
    m_Window->PollEvents();
}

}
