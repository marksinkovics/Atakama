#include "IconButton.hpp"

namespace Atakama::Editor
{

void IconButton(Ref<IconMap>& iconMap, IconMap::Icon icon, int* source, int value)
{
    ImGuiStyle& style = ImGui::GetStyle();
    glm::vec2 uv0 = iconMap->GetUVStartPos(icon);
    glm::vec2 uv1 = iconMap->GetUVEndPos(icon);
    ImVec4 tintColor = { 1, 1, 1, 1 };
    ImVec4 backgroundColor = style.Colors[ImGuiCol_Button];
    if (*source == value) {
        tintColor.w = 0.5;
        backgroundColor = style.Colors[ImGuiCol_ButtonActive];
    }

    ImGuiWindow* window = ImGui::GetCurrentWindow();
    const ImGuiID id = window->GetID(source + value);
    ImGui::PushID(value);
    if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(iconMap->GetId()), ImVec2(25, 25), { uv0.x, uv0.y }, { uv1.x, uv1.y }, 0, backgroundColor, tintColor))
    {
        *source = value;
    }
    ImGui::PopID();

}

}