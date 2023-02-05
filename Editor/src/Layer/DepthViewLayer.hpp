#ifndef ATAKAMA_EDITOR_DEPTH_VIEW_HPP
#define ATAKAMA_EDITOR_DEPTH_VIEW_HPP

#include <Atakama/Core/Layer.hpp>

namespace Atakama
{

class Engine;
class RenderPass;

namespace Editor
{

class DepthViewLayer: public Layer
{
public:
    DepthViewLayer();
    ~DepthViewLayer() = default;
    virtual void OnUpdateUI(float ts) override;
private:
    Ref<Engine> m_Engine;
    Ref<RenderPass> m_RenderPass;
};

}

}

#endif /* DepthViewLayer_hpp */
