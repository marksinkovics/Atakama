#ifndef ATAKAMA_ENGINE_HPP
#define ATAKAMA_ENGINE_HPP

#include <chrono>

namespace Atakama
{

class RenderPass;
class SkyBoxRenderPass;
class MainRenderPass;
class DebugRenderPass;
class EditorRenderPass;
class DepthViewRenderPass;
class OutlineRenderPass;
class ViewportRenderPass;
class RenderSystem;
class Profiler;
class Scene;

class Engine
{
public:
    struct Statistics
    {
        float CPUTime;
        float GPUTime;
        std::string Vendor;
        std::string Renderer;
        std::string Version;
        std::string ShadingLanguageVersion;
    };
public:

    void Init(Ref<Window>& window, Ref<Profiler>& profiler);
    void Shutdown();
    void Run();
    float CalculateDeltaTime();

    void UpdateRenderingViewportSize(glm::uvec2 size);

    Ref<SkyBoxRenderPass> GetSkyBoxRenderPass() { return m_SkyBoxRenderPass; }
    Ref<MainRenderPass> GetMainRenderPass() { return m_MainRenderPass; }
    Ref<DebugRenderPass> GetDebugRenderPass() { return m_DebugRenderPass; }
    Ref<DepthViewRenderPass> GetDepthViewRenderPass() { return m_DepthViewRenderPass; }
    Ref<OutlineRenderPass> GetOutlineRenderPass() { return m_OutlineRenderPass; }
    Ref<ViewportRenderPass> GetViewportRenderPass() { return m_ViewportRenderPass; }

    Ref<Scene> GetScene() { return m_Scene; };

    Statistics GetStatistics() { return m_Statistics; };

private:
    Statistics m_Statistics;

    std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime {std::chrono::high_resolution_clock::now()};
    float m_FrameTime;
    
    Ref<Scene> m_Scene;
    Ref<Window> m_Window;
    Ref<RenderSystem> m_RenderSystem;

    Ref<SkyBoxRenderPass> m_SkyBoxRenderPass;
    Ref<MainRenderPass> m_MainRenderPass;
    Ref<DebugRenderPass> m_DebugRenderPass;
    Ref<DepthViewRenderPass> m_DepthViewRenderPass;
    Ref<OutlineRenderPass> m_OutlineRenderPass;
    Ref<ViewportRenderPass> m_ViewportRenderPass;

    std::vector<Ref<RenderPass>> m_MainRenderPasses;
    std::vector<Ref<RenderPass>> m_PostRenderPasses;

    Ref<Profiler> m_Profiler;

    friend Application;
};

}

#endif
