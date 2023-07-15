#ifndef ATAKAMA_EDITOR_DEPTH_VIEW_LAYER_HPP
#define ATAKAMA_EDITOR_DEPTH_VIEW_LAYER_HPP

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
    DepthViewLayer(const EditorUIConfig& config);
    ~DepthViewLayer() = default;
    virtual void OnUpdateUI(float ts) override;
private:
    Ref<Engine> m_Engine;
    Ref<RenderPass> m_RenderPass;
    const EditorUIConfig& m_UIConfig;
};

}

}

#endif /* DepthViewLayer_hpp */
