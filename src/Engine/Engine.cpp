#include "Engine.hpp"

#include "Window.hpp"
#include "FileSystem.hpp"
#include "AssetManager.hpp"
#include "InputSystem.hpp"

#include "RenderSystem.hpp"

#include "RenderPass/MainRenderPass.hpp"
#include "RenderPass/DepthViewRenderPass.hpp"
#include "RenderPass/ViewportRenderPass.hpp"

#include "Events/WindowEvent.hpp"
#include "Events/EventDispatcher.hpp"


#include <GLFW/glfw3.h>


namespace OGLSample
{

void Engine::Init(Ref<Window>& window)
{
    m_Window = window;

    if (!IsEditor())
    {
        g_RuntimeGlobalContext.m_Dispatcher->subscribe<WindowFrameBufferResizeEvent>(std::bind(&Engine::OnWindowFrameBufferResize, this, std::placeholders::_1));
    }

    m_RenderSystem = RenderSystem::Create();
    m_RenderSystem->Init();
    m_RenderSystem->SetClearColor({0.0f, 0.0f, 0.4f, 0.0f});
    
    m_Camera = CreateRef<Camera>(Camera::Mode::Perspective);
    m_Camera->LookAt({5.0f, 5.f, 5.f}, {0.0f, 0.0f, 0.0f});
    m_Camera->Resize(m_Window->GetWidth(), m_Window->GetHeight());

    m_Scene = CreateRef<SandboxScene>();
    m_Scene->Init();

    m_perfMonitor = CreateRef<PerfMonitor>();

    m_MainRenderPass = CreateRef<MainRenderPass>(m_RenderSystem, m_Scene, m_Camera);
    m_DebugRenderPass = CreateRef<DebugRenderPass>(m_RenderSystem, m_Scene, m_Camera, m_MainRenderPass->GetFrameBuffer());

    m_DepthViewRenderPass = CreateRef<DepthViewRenderPass>(m_RenderSystem);
    m_DepthViewRenderPass->AddDependency(m_MainRenderPass);

    m_ViewportRenderPass = CreateRef<ViewportRenderPass>(m_RenderSystem);
    m_ViewportRenderPass->AddDependency(m_MainRenderPass);

    m_MainRenderPasses.push_back(m_MainRenderPass);
    m_MainRenderPasses.push_back(m_DebugRenderPass);
    m_PostRenderPasses.push_back(m_DepthViewRenderPass);

    if (!IsEditor())
    {
        m_PostRenderPasses.push_back(m_ViewportRenderPass);
    }

    m_UIRenderer = CreateRef<UIRenderer>(m_RenderSystem, m_Window);
    m_UIRenderer->Init();
    m_UIRenderViews.emplace_back(CreateRef<DepthRenderView>(m_DepthViewRenderPass));
    if (IsEditor())
    {
        m_UIRenderViews.emplace_back(CreateRef<ViewportRenderView>(m_MainRenderPass, std::bind(&Engine::UpdateRenderingViewportSize, this, std::placeholders::_1)));
    }
    m_UIRenderViews.emplace_back(CreateRef<StatRenderView>(m_perfMonitor, m_Scene));

    if (!IsEditor())
    {
        UpdateRenderingViewportSize(m_Window->GetFrameBufferSize());
    }
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

bool Engine::OnWindowFrameBufferResize(WindowFrameBufferResizeEvent& event)
{
    UpdateRenderingViewportSize({event.GetWidth(), event.GetHeight()});
}


void Engine::UpdateRenderingViewportSize(glm::uvec2 size)
{
    m_MainRenderPass->Resize(size);
    m_DepthViewRenderPass->Resize(size);
    m_Camera->Resize(size.x, size.y);
}

void Engine::Run()
{
    CalculateDeltaTime();
    
    m_Camera->Update(m_FrameTime);

    m_perfMonitor->StartCPUTimer();
    m_perfMonitor->StartGPUTimer();

    {
        for (const Ref<RenderPass>& renderPass : m_MainRenderPasses)
        {
            renderPass->Render();
        }

        for (const Ref<RenderPass>& renderPass : m_PostRenderPasses)
        {
            renderPass->Render();
        }
    }

    m_perfMonitor->StopGPUTimer();
    m_perfMonitor->StopCPUTimer();
    
    m_UIRenderer->Begin();
    {
        for (const Ref<UIRenderView>& renderView : m_UIRenderViews)
        {
            renderView->OnRender();
        }
    }
    m_UIRenderer->End();
    
    g_RuntimeGlobalContext.m_InputSystem->Clear();
    m_Window->SwapBuffers();
    m_Window->PollEvents();
}

}
