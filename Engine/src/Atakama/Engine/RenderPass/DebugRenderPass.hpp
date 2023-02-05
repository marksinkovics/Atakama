#ifndef ATAKAMA_DEBUG_RENDER_PASS_HPP
#define ATAKAMA_DEBUG_RENDER_PASS_HPP

#include "RenderPass.hpp"

namespace Atakama
{

class SimpleRenderer;
class PointLightRenderer;
class Mesh;
class Camera;
class Scene;

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
