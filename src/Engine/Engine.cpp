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

    lightingRenderer = CreateRef<LightingRenderer>();
    lightingRenderer->Init(m_RenderSystem, m_Camera);

    pointLightRenderer = CreateRef<PointLightRenderer>();
    pointLightRenderer->Init(m_RenderSystem, m_Camera);
            
    m_UIRenderer = CreateRef<UIRenderer>();
    m_UIRenderer->Init(m_Window);
    
    m_ScreenRenderer = CreateRef<ScreenRenderer>();
    m_ScreenRenderer->Init(m_RenderSystem, m_Camera);

    m_ScreenDepthRenderer = CreateRef<ScreenDepthRenderer>();
    m_ScreenDepthRenderer->Init(m_RenderSystem, m_Camera);
    
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

    m_perfMonitor->StartCPUTimer();
    m_perfMonitor->StartGPUTimer();
    
    m_ScreenRenderer->StartRecord();
    m_RenderSystem->SetViewport(0, 0, m_Window->GetFrameBufferWidth(), m_Window->GetFrameBufferHeight());
    m_RenderSystem->SetDepthTest(true);
    m_RenderSystem->SetClearColor({0.0f, 0.0f, 0.4f, 0.0f});
    m_RenderSystem->Clear();

    
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
    
    m_ScreenRenderer->StopRecord();
    
    m_RenderSystem->SetDepthTest(false);
    m_RenderSystem->SetClearColor({1.0f, 1.0f, 1.0f, 0.0f});
    m_RenderSystem->Clear();
    m_RenderSystem->SetViewport(0, 0, m_Window->GetFrameBufferWidth(), m_Window->GetFrameBufferHeight());

    m_ScreenRenderer->Begin();
    m_ScreenRenderer->Draw((float)(glfwGetTime()*10.0f), glm::vec2(m_Window->GetFrameBufferWidth(), m_Window->GetFrameBufferHeight()));
    m_ScreenRenderer->End();
    
    m_ScreenDepthRenderer->Begin();
    m_ScreenDepthRenderer->StartRecord();
    m_ScreenDepthRenderer->Draw((float)(glfwGetTime()*10.0f), glm::vec2(m_Window->GetFrameBufferWidth(), m_Window->GetFrameBufferHeight()), m_ScreenRenderer->GetFrameBuffer()->GetDepthTexture());
    m_ScreenDepthRenderer->StopRecord();
    m_ScreenRenderer->End();

    m_perfMonitor->StopGPUTimer();
    m_perfMonitor->StopCPUTimer();
    
    m_UIRenderer->Begin();
    m_UIRenderer->Draw(m_Scene,
                       m_perfMonitor,
                       m_ScreenRenderer->GetFrameBuffer()->GetColorTexture(),
                       m_ScreenDepthRenderer->GetFrameBuffer()->GetColorTexture()
                       );
    
    g_RuntimeGlobalContext.m_InputSystem->Clear();
    m_Window->SwapBuffers();
    m_Window->PollEvents();
}

}
