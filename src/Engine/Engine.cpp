#include "Engine.hpp"

#include "Window.hpp"
#include "FileSystem.hpp"
#include "AssetManager.hpp"
#include "InputSystem.hpp"

#include "OpenGL3/OpenGL3RenderSystem.hpp"

namespace OGLSample
{

void Engine::Init(Ref<Window>& window)
{
    m_Window = window;

    m_RenderSystem = RenderSystem::Create();
    m_RenderSystem->Init();
    m_RenderSystem->SetClearColor({0.0f, 0.0f, 0.4f, 0.0f});
    
    m_Camera = CreateRef<Camera>(Camera::Mode::Perspective);
    m_Camera->LookAt({5.0f, 5.f, 5.f});
        
    m_Scene = CreateRef<SandboxScene>();
    m_Scene->Init();

    simpleRenderer = CreateRef<SimpleRenderer>();
    simpleRenderer->Init(m_RenderSystem, m_Camera);

    textureRenderer = CreateRef<TextureRenderer>();
    textureRenderer->Init(m_RenderSystem, m_Camera);

    lightingRenderer = CreateRef<LightingRenderer>();
    lightingRenderer->Init(m_RenderSystem, m_Camera);

    pointLightRenderer = CreateRef<PointLightRenderer>();
    pointLightRenderer->Init(m_RenderSystem, m_Camera);
            
    m_UIRenderer = CreateRef<UIRenderer>();
    m_UIRenderer->Init(m_Window);
    
    m_perfMonitor = CreateRef<PerfMonitor>();
}

void Engine::Shutdown()
{

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
    
    m_Camera->Update(m_FrameTime);
 
    m_RenderSystem->Clear();
    
    m_UIRenderer->Begin();
    
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
    
    m_UIRenderer->Draw(m_Scene, m_perfMonitor);
    
    g_RuntimeGlobalContext.m_InputSystem->Clear();
    m_Window->SwapBuffers();
    m_Window->PollEvents();
}

}
