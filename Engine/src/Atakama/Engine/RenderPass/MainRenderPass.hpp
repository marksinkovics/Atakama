#ifndef ATAKAMA_MAIN_RENDER_PASS_HPP
#define ATAKAMA_MAIN_RENDER_PASS_HPP

#include "RenderPass.hpp"

namespace Atakama
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

}

#endif
