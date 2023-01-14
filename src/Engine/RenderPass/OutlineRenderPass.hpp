#ifndef OUTLINE_RENDER_PASS
#define OUTLINE_RENDER_PASS

#include "RenderPass.hpp"

namespace OGLSample
{

class Shader;
class Mesh;

class OutlineRenderPass: public RenderPass
{
public:
    OutlineRenderPass(Ref<RenderSystem> renderSystem);
    virtual ~OutlineRenderPass();
    virtual std::string GetName() override { return "Outline RenderPass"; }
protected:
    virtual void Draw() override;

private:
    Ref<Mesh> m_Mesh;
    Ref<Shader> m_Shader;
};


}

#endif
