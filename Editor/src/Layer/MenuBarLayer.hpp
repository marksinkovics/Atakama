#ifndef ATAKAMA_EDITOR_MENUBAR_LAYER_HPP
#define ATAKAMA_EDITOR_MENUBAR_LAYER_HPP

#include <Atakama/Core/Layer.hpp>

namespace Atakama
{

class Engine;
class RenderPass;

namespace Editor
{

class MenuBarLayer: public Layer
{
public:
    MenuBarLayer();
    ~MenuBarLayer() = default;
    virtual void OnUpdateUI(float ts) override;
};

}

}

#endif /* DepthViewLayer_hpp */
