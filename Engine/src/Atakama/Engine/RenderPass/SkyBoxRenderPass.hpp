#ifndef ATAKAMA_SKYBOX_RENDER_PASS_HPP
#define ATAKAMA_SKYBOX_RENDER_PASS_HPP

#include "RenderPass.hpp"

namespace Atakama
{

class Texture;
class RenderSystem;
class Shader;
class Mesh;
class Camera;

class SkyBoxRenderPass: public RenderPass
{
public:
    SkyBoxRenderPass(Ref<RenderSystem> renderSystem, Ref<Camera>& camera);
    virtual ~SkyBoxRenderPass() = default;
protected:
    virtual void Draw() override;
    virtual std::string GetName() override;
private:
    Ref<Camera> m_Camera;
    Ref<Texture> m_Texture;
    Ref<Shader> m_Shader;
    Ref<Mesh> m_Mesh;
};

}

#endif /* SkyBoxRenderPass_hpp */
