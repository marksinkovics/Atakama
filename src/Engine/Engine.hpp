#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Shader.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"

#include "Engine/Lights/PointLight.hpp"
#include "Engine/RenderSystem.hpp"
#include "Renderer/SimpleRenderer.hpp"
#include "Renderer/LightingRenderer.hpp"
#include "Renderer/PointLightRenderer.hpp"
#include "Renderer/UIRenderer.hpp"
#include "Renderer/ScreenRenderer.hpp"
#include "Perf/PerfMonitor.hpp"

#include "Scene.hpp"

#include <chrono>

namespace OGLSample
{

class Engine
{
public:
    void Init(Ref<Window>& window);
    void Shutdown();
    void Run();
    void CalculateDeltaTime();
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime {std::chrono::high_resolution_clock::now()};
    float m_FrameTime;
    
    Ref<Scene> m_Scene;
    Ref<Window> m_Window;
    Ref<RenderSystem> m_RenderSystem;
    Ref<Camera> m_Camera;
    
    Ref<SimpleRenderer> simpleRenderer;
    Ref<LightingRenderer> lightingRenderer;
    Ref<PointLightRenderer> pointLightRenderer;
    Ref<UIRenderer> m_UIRenderer;
    Ref<ScreenRenderer> m_ScreenRenderer;
        
    Ref<PerfMonitor> m_perfMonitor;
};

}

#endif
