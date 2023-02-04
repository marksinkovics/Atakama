#ifndef ATAKAMA_UIRENDERER_HPP
#define ATAKAMA_UIRENDERER_HPP

namespace Atakama
{

class Scene;
class PerfMonitor;
class Window;
class RenderPass;
class RenderSystem;

class UIRenderer
{
public:
    UIRenderer(Ref<RenderSystem>& renderSystem, Ref<Window>& window);
    virtual ~UIRenderer();
    void Begin();
    void End();
private:
    Ref<RenderSystem> m_RenderSystem;
    Ref<Window> m_Window;
};

class UIRenderView
{
public:
    virtual ~UIRenderView() = default;
    virtual void OnRender() = 0;
};

class DepthRenderView: public UIRenderView
{
public:
    DepthRenderView(Ref<RenderPass> renderPass);
    virtual ~DepthRenderView() = default;
    virtual void OnRender() override;
private:
    Ref<RenderPass> m_RenderPass;
};

class ViewportRenderView: public UIRenderView
{
public:
    typedef std::function<void(glm::uvec2)> CallbackFunc;
    ViewportRenderView(Ref<RenderPass> renderPass, const CallbackFunc& callback = nullptr);
    virtual ~ViewportRenderView() = default;
    virtual void OnRender() override;
private:
    Ref<RenderPass> m_RenderPass;
    bool m_ViewportFocused = false;
    bool m_ViewportHovered = false;
    glm::uvec2 m_ViewportSize;
    glm::vec2 m_ViewportBounds[2];
    CallbackFunc m_Callback;
    int m_MeshId;
};

class StatRenderView: public UIRenderView
{
public:
    StatRenderView(Ref<PerfMonitor>& monitor, Ref<Scene>& scene);
    virtual ~StatRenderView() = default;
    virtual void OnRender() override;
private:
    Ref<PerfMonitor> m_Monitor;
    Ref<Scene> m_Scene;
};

}

#endif
