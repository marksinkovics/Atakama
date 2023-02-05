#include "Engine.hpp"

#include "Atakama/Core/Window.hpp"
#include <Atakama/Core/FileSystem.hpp>
#include "AssetManager.hpp"
#include "Atakama/Core/InputSystem.hpp"

#include "RenderSystem.hpp"

#include "RenderPass/SkyBoxRenderPass.hpp"
#include "RenderPass/MainRenderPass.hpp"
#include "RenderPass/DebugRenderPass.hpp"
#include "RenderPass/DepthViewRenderPass.hpp"
#include "RenderPass/OutlineRenderPass.hpp"
#include "RenderPass/ViewportRenderPass.hpp"

#include "Atakama/Events/WindowEvent.hpp"
#include "Atakama/Events/EventDispatcher.hpp"
#include "Atakama/Events/MouseEvent.hpp"

#include "Camera.hpp"
#include "CameraSystem.hpp"

#include <GLFW/glfw3.h>


namespace Atakama
{

void Engine::Init(Ref<Window>& window, Ref<Profiler>& profiler)
{
    m_Window = window;
    m_Profiler = profiler;

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
    m_ViewportRenderPass->AddDependency(m_MainRenderPass);

    m_MainRenderPasses.push_back(m_MainRenderPass);
    m_MainRenderPasses.push_back(m_DebugRenderPass);
    m_MainRenderPasses.push_back(m_SkyBoxRenderPass);
    m_PostRenderPasses.push_back(m_DepthViewRenderPass);
    m_PostRenderPasses.push_back(m_OutlineRenderPass);
    m_PostRenderPasses.push_back(m_ViewportRenderPass);
}

void Engine::Shutdown()
{

}

float Engine::CalculateDeltaTime()
{
    auto timePoint = std::chrono::high_resolution_clock::now();
    m_FrameTime = std::chrono::duration<float, std::chrono::seconds::period>(timePoint - m_LastTime).count();
    m_LastTime = timePoint;
    return m_FrameTime;
}

bool Engine::OnMouseScrollEvent(MouseScrolledEvent &event)
{
    m_Cameras[0]->Zoom(event.GetYOffset() * 0.1f);
}

void Engine::UpdateRenderingViewportSize(glm::uvec2 size)
{
    m_MainRenderPass->Resize(size);

    if (m_DepthViewRenderPass->IsEnabled())
    {
        m_DepthViewRenderPass->Resize(size);
    }

    if (m_OutlineRenderPass->IsEnabled())
    {
        m_OutlineRenderPass->Resize(size);
    }

    m_Cameras[0]->Resize(size.x, size.y);
}

void Engine::Run()
{
    m_CameraSystem->Update(m_Cameras[0], m_FrameTime);

    m_Profiler->Start();

    {
        for (const Ref<RenderPass>& renderPass : m_MainRenderPasses)
        {
            if (!renderPass->IsEnabled())
                continue;
            renderPass->Render();
        }

        for (const Ref<RenderPass>& renderPass : m_PostRenderPasses)
        {
            if (!renderPass->IsEnabled())
                continue;
            renderPass->Render();
        }
    }

    m_Profiler->Stop();
}

}
