#ifndef ATAKAMA_EDITOR_UI_CONFIG_HPP
#define ATAKAMA_EDITOR_UI_CONFIG_HPP

#include <imgui.h>

namespace Atakama::Editor
{

struct EditorUIConfig
{
    ImGuiWindowClass editorTopLevelClass;
    ImGuiWindowClass documentClass;
    ImGuiWindowClass projectSettingsClass;
    ImGuiID editorTopLevelDockSpace;
    ImGuiID documentDockSpace;
    ImGuiID projectSettingsDockSpace;
};

enum class WindowId
{
    Document,
};

struct WindowConfig
{
    std::string Name;
    std::string Id;

    std::string GetImGuiWindowId() const;
    std::string GetLayerName() const;
};

}

#endif