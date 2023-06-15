#ifndef ATAKAMA_EDITOR_MENUBAR_LAYER_HPP
#define ATAKAMA_EDITOR_MENUBAR_LAYER_HPP

#include <Atakama/Core/Layer.hpp>
#include <Atakama/ImGui/FileDialog.hpp>

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
private:
    bool m_fileDialogOpen { false };
    FileDialogInfo m_fileDialogInfo;
};

}

}

#endif /* DepthViewLayer_hpp */
