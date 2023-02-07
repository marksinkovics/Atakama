#ifndef ATAKAMA_MAIN_RENDER_PASS_HPP
#define ATAKAMA_MAIN_RENDER_PASS_HPP

#include "RenderPass.hpp"

namespace Atakama
{

class Scene;
class Shader;

class MainRenderPass: public SceneRenderPass
{
public:
    MainRenderPass(Ref<RenderSystem> renderSystem, Ref<Scene> scene);
    virtual ~MainRenderPass() = default;
protected:
    virtual void Draw() override;
    virtual std::string GetName() override;
private:
    Ref<Shader> m_Shader;
};

}

#endif
