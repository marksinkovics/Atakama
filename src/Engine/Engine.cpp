#include "Engine.hpp"

#include "Window.hpp"
#include "FileSystem.hpp"
#include "AssetManager.hpp"
#include "InputSystem.hpp"

#include "RenderSystem.hpp"

#include "RenderPass/SkyBoxRenderPass.hpp"
#include "RenderPass/MainRenderPass.hpp"
#include "RenderPass/DepthViewRenderPass.hpp"
#include "RenderPass/OutlineRenderPass.hpp"
#include "RenderPass/ViewportRenderPass.hpp"

#include "Events/WindowEvent.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/MouseEvent.hpp"

#include "Camera.hpp"
#include "CameraSystem.hpp"

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

    g_RuntimeGlobalContext.m_Dispatcher->subscribe<MouseScrolledEvent>(std::bind(&Engine::OnMouseScrollEvent, this, std::placeholders::_1));

    m_RenderSystem = RenderSystem::Create();
    m_RenderSystem->Init();
    m_RenderSystem->SetClearColor({0.0f, 0.0f, 0.4f, 0.0f});

    m_CameraSystem = CreateRef<CameraSystem>();
    m_Cameras.push_back(CreateRef<Camera>(Camera::Mode::Perspective));
    m_CameraSystem->LookAt(m_Cameras[0], {5.0f, 5.f, 5.f}, {0.0f, 0.0f, 0.0f});
    m_Cameras[0]->Resize(m_Window->GetWidth(), m_Window->GetHeight());

    m_Scene = CreateRef<SandboxScene>();
    m_Scene->Init();

    m_perfMonitor = CreateRef<PerfMonitor>();

    m_MainRenderPass = CreateRef<MainRenderPass>(m_RenderSystem, m_Scene, m_Cameras[0]);
    m_DebugRenderPass = CreateRef<DebugRenderPass>(m_RenderSystem, m_Scene, m_Cameras[0]);
    m_DebugRenderPass->SetFrameBuffer(m_MainRenderPass->GetFrameBuffer());
    m_SkyBoxRenderPass = CreateRef<SkyBoxRenderPass>(m_RenderSystem, m_Cameras[0]);
    m_SkyBoxRenderPass->SetFrameBuffer(m_MainRenderPass->GetFrameBuffer());

    m_DepthViewRenderPass = CreateRef<DepthViewRenderPass>(m_RenderSystem);
    m_DepthViewRenderPass->AddDependency(m_MainRenderPass);

    m_OutlineRenderPass = CreateRef<OutlineRenderPass>(m_RenderSystem);
    m_OutlineRenderPass->AddDependency(m_MainRenderPass);

    m_ViewportRenderPass = CreateRef<ViewportRenderPass>(m_RenderSystem);
    m_ViewportRenderPass->AddDependency(m_OutlineRenderPass);

    m_MainRenderPasses.push_back(m_MainRenderPass);
    m_MainRenderPasses.push_back(m_DebugRenderPass);
    m_MainRenderPasses.push_back(m_SkyBoxRenderPass);
    m_PostRenderPasses.push_back(m_DepthViewRenderPass);
    m_PostRenderPasses.push_back(m_OutlineRenderPass);


    if (!IsEditor())
    {
        m_PostRenderPasses.push_back(m_ViewportRenderPass);
    }

    m_UIRenderer = CreateRef<UIRenderer>(m_RenderSystem, m_Window);
    m_UIRenderViews.emplace_back(CreateRef<DepthRenderView>(m_DepthViewRenderPass));

    if (IsEditor())
    {
        m_UIRenderViews.emplace_back(CreateRef<ViewportRenderView>(m_OutlineRenderPass, std::bind(&Engine::UpdateRenderingViewportSize, this, std::placeholders::_1)));
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

bool Engine::OnMouseScrollEvent(MouseScrolledEvent &event)
{
    m_Cameras[0]->Zoom(event.GetYOffset() * 0.1f);
}

void Engine::UpdateRenderingViewportSize(glm::uvec2 size)
{
    m_MainRenderPass->Resize(size);
    m_DepthViewRenderPass->Resize(size);
    m_OutlineRenderPass->Resize(size);
    m_Cameras[0]->Resize(size.x, size.y);
}

void Engine::Run()
{
    CalculateDeltaTime();

    m_CameraSystem->Update(m_Cameras[0], m_FrameTime);

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
