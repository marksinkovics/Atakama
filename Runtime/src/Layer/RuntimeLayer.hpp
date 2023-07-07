#ifndef ATAKAMA_RUNTIME_LAYER_HPP
#define ATAKAMA_RUNTIME_LAYER_HPP

#include <Atakama/Core/Layer.hpp>

namespace Atakama
{

class Application;
class InputSystem;
class CameraSystem;

namespace Runtime
{

class RuntimeLayer : public Layer
{
public:
    RuntimeLayer();
    ~RuntimeLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(float ts) override;
    virtual void OnUpdateUI(float ts) override;
private:
    Application* m_Application;

    Ref<InputSystem> m_InputSystem;
    Ref<CameraSystem> m_CameraSystem;

};

}

}

#endif
