#ifndef ATAKAMA_EDITOR_CONFIG_LAYER_HPP
#define ATAKAMA_EDITOR_CONFIG_LAYER_HPP

#include "EditorUIConfig.hpp"

#include <Atakama/Core/Layer.hpp>

namespace Atakama::Editor
{
    class EditorApplication;

    class EditorConfigLayer : public Layer
    {
    public:
        EditorConfigLayer(EditorUIConfig& config);
        ~EditorConfigLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdateUI(float ts) override;
    private:
        void Config();
    private:
        EditorApplication* m_Application;
        EditorUIConfig& m_UIConfig;
        const float toolbarSize = 25;
    };

}

#endif
