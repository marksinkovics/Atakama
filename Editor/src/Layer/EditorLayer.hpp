#ifndef ATAKAMA_EDITOR_LAYER_HPP
#define ATAKAMA_EDITOR_LAYER_HPP

#include "EditorUIConfig.hpp"

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
    const EditorUIConfig& GetUIConfig() const;
    EditorUIConfig& GetUIConfig();
private:
    EditorUIConfig m_UIConfig;
};

}

#endif
