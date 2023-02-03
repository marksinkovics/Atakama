#ifndef ATAKAMA_EDITOR_RENDER_PASS_HPP
#define ATAKAMA_EDITOR_RENDER_PASS_HPP

#include "RenderPass.hpp"

namespace Atakama
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
