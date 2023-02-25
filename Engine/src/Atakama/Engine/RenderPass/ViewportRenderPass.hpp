#ifndef ATAKAMA_VIEWPORT_RENDER_PASS_HPP
#define ATAKAMA_VIEWPORT_RENDER_PASS_HPP

#include "RenderPass.hpp"

namespace Atakama
{

class Shader;
class MeshObject;

class ViewportRenderPass: public RenderPass
{
public:
    ViewportRenderPass(Ref<RenderSystem> renderSystem);
    virtual ~ViewportRenderPass();
    virtual std::string GetName() override { return "Viewport RenderPass"; }
protected:
    virtual void Draw() override;

private:
    Ref<MeshObject> m_Mesh;
    Ref<Shader> m_Shader;
};


}

#endif
