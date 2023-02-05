#ifndef ATAKAMA_EDITOR_RENDER_PASS_HPP
#define ATAKAMA_EDITOR_RENDER_PASS_HPP

#include "RenderPass.hpp"

namespace Atakama
{

class Profiler;

class EditorRenderPass: public RenderPass
{
public:
    EditorRenderPass(Ref<RenderSystem> renderSystem, Ref<Profiler>& profiler);
    virtual std::string GetName() override { return "Editor RenderPass"; }
private:
    bool m_ViewportFocused = false;
    bool m_ViewportHovered = false;

    Ref<Profiler>& m_Profiler;
};

}

#endif
