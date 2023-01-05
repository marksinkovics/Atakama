#ifndef DEPTH_VIEW_RENDER_PASS
#define DEPTH_VIEW_RENDER_PASS

#include "RenderPass.hpp"

namespace OGLSample
{

class Shader;
class Mesh;

class DepthViewRenderPass: public RenderPass
{
public:
    DepthViewRenderPass(Ref<RenderSystem> renderSystem);
    virtual ~DepthViewRenderPass();
    virtual std::string GetName() override { return "Depth RenderPass"; }
protected:
    virtual void Draw() override;

private:
    Ref<Mesh> m_Mesh;
    Ref<Shader> m_Shader;
};

}

#endif
