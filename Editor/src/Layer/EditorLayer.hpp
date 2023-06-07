#ifndef ATAKAMA_EDITOR_LAYER_HPP
#define ATAKAMA_EDITOR_LAYER_HPP

#include <Atakama/Core/Layer.hpp>

namespace Atakama::Editor
{

class EditorLayer : public Layer
{
public:
    EditorLayer();
    ~EditorLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdateUI(float ts) override;
};

}

#endif
