#ifndef ATAKAMA_EDITOR_VIEWPORT_LAYER_CPP
#define ATAKAMA_EDITOR_VIEWPORT_LAYER_CPP

#include <Atakama/Core/Layer.hpp>

namespace Atakama
{

class Engine;
class RenderPass;
class InputSystem;
class CameraSystem;

}

namespace Atakama::Editor
{

class ViewportLayer: public Layer
{
public:
    typedef std::function<void(glm::uvec2)> CallbackFunc;

    ViewportLayer();
    virtual ~ViewportLayer() = default;
    virtual void OnAttach() override;
    virtual void OnUpdate(float ts) override;
    virtual void OnUpdateUI(float ts) override;
private:
    Ref<Engine> m_Engine;
    Ref<RenderPass> m_RenderPass;
    Ref<InputSystem> m_InputSystem;
    Ref<CameraSystem> m_CameraSystem;

    bool m_ViewportFocused = false;
    bool m_ViewportHovered = false;
    bool m_ToolbarHovered = false;

    glm::uvec2 m_ViewportSize;
    glm::vec2 m_ViewportBounds[2];

    CallbackFunc m_Callback;

    int m_MeshId;

    int m_GizmoType;

    bool m_EnableGizmoSnapping { false };
};

}



#endif
