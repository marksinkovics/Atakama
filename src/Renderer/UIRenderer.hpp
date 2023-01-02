#ifndef UIRENDERER_HPP
#define UIRENDERER_HPP

#include "Renderer/Renderer.hpp"

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
    void Draw(Ref<Scene>& scene, Ref<PerfMonitor>& perfMonitor, Ref<Texture> colorTexture, Ref<Texture> depthTexture);
private:
    bool m_ViewportFocused = false;
    bool m_ViewportHovered = false;
    glm::uvec2 m_ViewportSize;
};

}

#endif
