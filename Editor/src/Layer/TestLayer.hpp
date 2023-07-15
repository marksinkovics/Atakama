#ifndef ATAKAMA_TEST_LAYER_HPP
#define ATAKAMA_TEST_LAYER_HPP

#include <Atakama/Core/Layer.hpp>

#include <imgui.h>

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

    ImGuiWindowClass editorTopLevelClass;
    ImGuiWindowClass documentClass;
    ImGuiWindowClass projectSettingsClass;
    ImGuiID editorTopLevelDockSpace;
    ImGuiID documentDockSpace;
    ImGuiID projectSettingsDockSpace;
};

}

#endif
