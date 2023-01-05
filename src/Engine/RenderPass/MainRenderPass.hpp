#ifndef MAIN_RENDER_PASS_HPP
#define MAIN_RENDER_PASS_HPP

#include "RenderPass.hpp"

namespace OGLSample
{

class Camera;
class Scene;
class LightingRenderer;

class MainRenderPass: public RenderPass
{
public:
    MainRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene> scene, Ref<Camera> camera);
    virtual ~MainRenderPass() = default;

protected:
    virtual void Draw() override;
    virtual std::string GetName() override;
private:
    Ref<Scene> m_Scene;
    Ref<Camera> m_Camera;
    Ref<LightingRenderer> m_Renderer;
};

class SimpleRenderer;
class PointLightRenderer;

class DebugRenderPass: public RenderPass
{
public:
    DebugRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene> scene, Ref<Camera> camera, Ref<FrameBuffer> frameBuffer);
    virtual ~DebugRenderPass() = default;

protected:
    virtual void Draw() override;
    virtual std::string GetName() override;
private:
    Ref<Scene> m_Scene;
    Ref<Camera> m_Camera;
    Ref<SimpleRenderer> m_SimpleRenderer;
    Ref<PointLightRenderer> m_BillboardRenderer;
};

}

#endif
