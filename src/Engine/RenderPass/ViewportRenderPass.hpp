#ifndef VIEWPORT_RENDER_PASS
#define VIEWPORT_RENDER_PASS

#include "RenderPass.hpp"

namespace OGLSample
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
