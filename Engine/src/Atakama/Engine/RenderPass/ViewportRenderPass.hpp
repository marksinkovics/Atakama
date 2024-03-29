#ifndef ATAKAMA_VIEWPORT_RENDER_PASS_HPP
#define ATAKAMA_VIEWPORT_RENDER_PASS_HPP

#include "RenderPass.hpp"

namespace Atakama
{

class Shader;
class Mesh;

class ViewportRenderPass: public RenderPass
{
public:
    ViewportRenderPass(Ref<RenderSystem> renderSystem);
    virtual ~ViewportRenderPass();
    virtual std::string GetName() override { return "Viewport RenderPass"; }
protected:
    virtual void Draw() override;

private:
    Ref<Mesh> m_Mesh;
    Ref<Shader> m_Shader;
};


}

#endif
