#ifndef ATAKAMA_PROJECT_SETTINGS_LAYER_HPP
#define ATAKAMA_PROJECT_SETTINGS_LAYER_HPP

#include "EditorUIConfig.hpp"

#include <Atakama/Core/Layer.hpp>

namespace Atakama::Editor
{
    class EditorApplication;

    class ProjectSettingsLayer : public Layer
    {
    public:
        ProjectSettingsLayer();
        ~ProjectSettingsLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdateUI(float ts) override;
    private:
        EditorApplication* m_Application;
        EditorUIConfig& m_UIConfig;
    };

}

#endif
