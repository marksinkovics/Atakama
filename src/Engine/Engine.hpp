#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Shader.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"

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
class ViewportRenderPass;
class WindowFrameBufferResizeEvent;

class Engine
{
public:
    void Init(Ref<Window>& window);
    void Shutdown();
    void Run();
    void CalculateDeltaTime();

    bool OnWindowFrameBufferResize(WindowFrameBufferResizeEvent& event);
    void UpdateRenderingViewportSize(glm::uvec2 size);

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime {std::chrono::high_resolution_clock::now()};
    float m_FrameTime;
    
    Ref<Scene> m_Scene;
    Ref<Window> m_Window;
    Ref<RenderSystem> m_RenderSystem;
    Ref<Camera> m_Camera;

    Ref<SkyBoxRenderPass> m_SkyBoxRenderPass;
    Ref<MainRenderPass> m_MainRenderPass;
    Ref<DebugRenderPass> m_DebugRenderPass;
    Ref<DepthViewRenderPass> m_DepthViewRenderPass;
    Ref<ViewportRenderPass> m_ViewportRenderPass;

    std::vector<Ref<RenderPass>> m_MainRenderPasses;
    std::vector<Ref<RenderPass>> m_PostRenderPasses;
    
    Ref<UIRenderer> m_UIRenderer;
    std::vector<Ref<UIRenderView>> m_UIRenderViews;

    Ref<PerfMonitor> m_perfMonitor;
};

}

#endif
