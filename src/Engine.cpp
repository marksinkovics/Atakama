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

void Engine::Init(Ref<Window>& window, Ref<RenderSystem>& renderSystem)
{
    m_Window = window;
    m_RenderSystem = renderSystem;
    m_RenderSystem->Init();
    m_RenderSystem->SetClearColor({0.0f, 0.0f, 0.4f, 0.0f});
    
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
    
    m_perfMonitor = CreateRef<PerfMonitor>();
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
    m_RenderSystem->Clear();
    
    CalculateDeltaTime();
    
    m_Camera->UpdateFrameTime(m_FrameTime);
    m_Camera->Update(m_FrameTime);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    m_perfMonitor->StartCPUTimer();
    m_perfMonitor->StartGPUTimer();
    
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

    m_perfMonitor->StopGPUTimer();
    m_perfMonitor->StopCPUTimer();
    
    ImGui::Begin("ImGui Window");
    ImGui::Text("CPU time: %f ms", m_perfMonitor->GetCPUTime());
    ImGui::Text("GPU time: %f ms", m_perfMonitor->GetGPUTime());

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
