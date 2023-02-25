#ifndef ATAKAMA_DEPTH_VIEW_RENDER_PASS_HPP
#define ATAKAMA_DEPTH_VIEW_RENDER_PASS_HPP

#include "RenderPass.hpp"

namespace Atakama
{

class Shader;
class MeshObject;

class DepthViewRenderPass: public RenderPass
{
public:
    DepthViewRenderPass(Ref<RenderSystem> renderSystem);
    virtual ~DepthViewRenderPass();
    virtual std::string GetName() override { return "Depth RenderPass"; }
protected:
    virtual void Draw() override;

private:
    Ref<MeshObject> m_Mesh;
    Ref<Shader> m_Shader;
};

}

#endif
