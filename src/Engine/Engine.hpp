#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Shader.hpp"
#include "Mesh.hpp"

#include "Engine/RenderSystem.hpp"
#include "Renderer/UIRenderer.hpp"
#include "Perf/PerfMonitor.hpp"

#include "Scene.hpp"

#include <chrono>

namespace OGLSample
{

class RenderPass;
class SkyBoxRenderPass;
class MainRenderPass;
class DebugRenderPass;
class EditorRenderPass;
class DepthViewRenderPass;
class OutlineRenderPass;
class ViewportRenderPass;
class WindowFrameBufferResizeEvent;
class MouseScrolledEvent;

class CameraSystem;
class Camera;

class Engine
{
public:
    void Init(Ref<Window>& window);
    void Shutdown();
    void Run();
    void CalculateDeltaTime();

    bool OnWindowFrameBufferResize(WindowFrameBufferResizeEvent& event);
    bool OnMouseScrollEvent(MouseScrolledEvent& event);
    void UpdateRenderingViewportSize(glm::uvec2 size);

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime {std::chrono::high_resolution_clock::now()};
    float m_FrameTime;
    
    Ref<Scene> m_Scene;
    Ref<Window> m_Window;
    Ref<RenderSystem> m_RenderSystem;

    std::vector<Ref<Camera>> m_Cameras;
    Ref<CameraSystem> m_CameraSystem;

    Ref<SkyBoxRenderPass> m_SkyBoxRenderPass;
    Ref<MainRenderPass> m_MainRenderPass;
    Ref<DebugRenderPass> m_DebugRenderPass;
    Ref<DepthViewRenderPass> m_DepthViewRenderPass;
    Ref<OutlineRenderPass> m_OutlineRenderPass;
    Ref<ViewportRenderPass> m_ViewportRenderPass;

    std::vector<Ref<RenderPass>> m_MainRenderPasses;
    std::vector<Ref<RenderPass>> m_PostRenderPasses;
    
    Ref<UIRenderer> m_UIRenderer;
    std::vector<Ref<UIRenderView>> m_UIRenderViews;

    Ref<PerfMonitor> m_perfMonitor;
};

}

#endif
