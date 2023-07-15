#ifndef ATAKAMA_DOCUMENT_LAYER_HPP
#define ATAKAMA_DOCUMENT_LAYER_HPP

#include <Atakama/Core/Layer.hpp>

namespace Atakama::Editor
{
    class EditorApplication;

    class DocumentLayer : public Layer
    {
    public:
        DocumentLayer(WindowConfig& windowConfig, const EditorUIConfig& editorUIConfig);
        ~DocumentLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdateUI(float ts) override;
    private:
        EditorApplication* m_Application;
        const EditorUIConfig& m_UIConfig;
        WindowConfig& m_WindowConfig;
        const float toolbarSize = 25;
    };

}

#endif
