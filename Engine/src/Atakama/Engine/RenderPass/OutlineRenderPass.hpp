#ifndef ATAKAMA_OUTLINE_RENDER_PASS_HPP
#define ATAKAMA_OUTLINE_RENDER_PASS_HPP

#include "RenderPass.hpp"

namespace Atakama
{

class Scene;
class Shader;
class Mesh;

class OutlineRenderPass: public SceneRenderPass
{
public:
    OutlineRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene> scene);
    virtual ~OutlineRenderPass();
protected:
    virtual void Draw() override;
    virtual std::string GetName() override;
private:
    Ref<Mesh> m_Mesh;
    Ref<Shader> m_Shader;
};

}

#endif
