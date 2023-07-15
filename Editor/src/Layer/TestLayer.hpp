#ifndef ATAKAMA_TEST_LAYER_HPP
#define ATAKAMA_TEST_LAYER_HPP

#include <Atakama/Core/Layer.hpp>

namespace Atakama::Editor
{

class EditorApplication;

class TestLayer: public Layer
{
public:
    TestLayer();
    ~TestLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdateUI(float ts) override;
private:
    EditorApplication* m_Application;
};

}

#endif
