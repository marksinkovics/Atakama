#ifndef UIRENDERER_HPP
#define UIRENDERER_HPP

#include "Renderer/Renderer.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace OGLSample
{

class Scene;
class PerfMonitor;
class FrameBuffer;

class UIRenderer: public Renderer
{
public:
    void Init(Ref<Window>& window);
    void Shutdown();
    void Begin();
    void Draw(Ref<Scene>& scene, Ref<PerfMonitor>& perfMonitor, Ref<FrameBuffer>& frameBuffer);
};

}

#endif
