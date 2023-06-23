#ifndef ATAKAMA_DEBUG_RENDER_PASS_HPP
#define ATAKAMA_DEBUG_RENDER_PASS_HPP

#include "RenderPass.hpp"

namespace Atakama
{

class Scene;
class Shader;
class Mesh;

class DebugRenderPass: public SceneRenderPass
{
public:
    DebugRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene> scene);
    virtual ~DebugRenderPass() = default;
protected:
    virtual void Draw() override;
    virtual std::string GetName() override;
private:
    Ref<Shader> m_SimpleShader;
    Ref<Shader> m_PointLightShader;
    Ref<Shader> m_GridShader;

    Ref<Mesh> m_Grid;
};

}

#endif
