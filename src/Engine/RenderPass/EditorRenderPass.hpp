#ifndef EDITOR_RENDER_PASS
#define EDITOR_RENDER_PASS

#include "RenderPass.hpp"

namespace OGLSample
{

class PerfMonitor;

class EditorRenderPass: public RenderPass
{
public:
    EditorRenderPass(Ref<RenderSystem> renderSystem, Ref<PerfMonitor>& perfMonitor);
    virtual std::string GetName() override { return "Editor RenderPass"; }
private:
    bool m_ViewportFocused = false;
    bool m_ViewportHovered = false;

    Ref<PerfMonitor>& m_perfMonitor;
};

}

#endif
