#ifndef ATAKAMA_IMGUI_LAYER_HPP
#define ATAKAMA_IMGUI_LAYER_HPP

#include "Atakama/Core/Layer.hpp"

namespace Atakama
{

class Window;
class RenderSystem;

class ImGuiLayer: public Layer
{
public:
    ImGuiLayer(Ref<RenderSystem>& renderSystem, Ref<Window>& window);
    ~ImGuiLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void Begin();
    void End();
protected:
    Ref<Window> m_Window;
    Ref<RenderSystem> m_RenderSystem;
private:
    void SetCustomTheme();
};

}

#endif /* ImGuiLayer_hpp */
