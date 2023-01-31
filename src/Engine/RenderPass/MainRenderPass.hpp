#ifndef MAIN_RENDER_PASS_HPP
#define MAIN_RENDER_PASS_HPP

#include "RenderPass.hpp"

namespace OGLSample
{

class Camera;
class Scene;
class LightingRenderer;

class MainRenderPass: public SceneRenderPass
{
public:
    MainRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene> scene, Ref<Camera>& camera);
    virtual ~MainRenderPass() = default;
protected:
    virtual void Draw() override;
    virtual std::string GetName() override;
private:
    Ref<Camera> m_Camera;
    Ref<LightingRenderer> m_Renderer;
};

class SimpleRenderer;
class PointLightRenderer;
class Mesh;

class DebugRenderPass: public SceneRenderPass
{
public:
    DebugRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene> scene, Ref<Camera>& camera);
    virtual ~DebugRenderPass() = default;
protected:
    virtual void Draw() override;
    virtual std::string GetName() override;
private:
    Ref<Mesh> m_AxisMesh;
    Ref<Camera> m_Camera;
    Ref<SimpleRenderer> m_SimpleRenderer;
    Ref<PointLightRenderer> m_BillboardRenderer;
};

}

#endif
