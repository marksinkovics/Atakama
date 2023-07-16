#ifndef ATAKAMA_DOCUMENT_LAYER_HPP
#define ATAKAMA_DOCUMENT_LAYER_HPP

#include <Atakama/Core/Layer.hpp>

namespace Atakama::Editor
{
    class EditorApplication;

    class DocumentLayer : public Layer
    {
    public:
        DocumentLayer();
        ~DocumentLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdateUI(float ts) override;
    private:
        EditorApplication* m_Application;
        EditorUIConfig& m_UIConfig;
        const float toolbarSize = 25;
    };

}

#endif
