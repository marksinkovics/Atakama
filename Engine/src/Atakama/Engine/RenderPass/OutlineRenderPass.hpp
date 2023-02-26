#ifndef ATAKAMA_OUTLINE_RENDER_PASS_HPP
#define ATAKAMA_OUTLINE_RENDER_PASS_HPP

#include "RenderPass.hpp"

namespace Atakama
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
