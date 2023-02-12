#include "SceneLayer.hpp"

#include <Atakama/Engine/Engine.hpp>
#include <Atakama/Scene/Entity.hpp>
#include <Atakama/Scene/Scene.hpp>
#include <Atakama/Scene/Components/Components.hpp>

#include <imgui.h>
#include <imgui_internal.h>

#include <string>
#include <string.h>

namespace Atakama::Editor
{

SceneLayer::SceneLayer()
: Layer("Scene Layer")
{
    m_Engine = g_RuntimeGlobalContext.m_Engine;
    m_Scene = m_Engine->GetScene();
}

void SceneLayer::OnUpdateUI(float ts)
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;

    if (g_RuntimeEditorContext.SceneViewOpen)
    {
        ImGui::Begin("Scene View", &g_RuntimeEditorContext.SceneViewOpen, window_flags);
        UpdateEntityList();
        ImGui::End();
    }

    if (g_RuntimeEditorContext.ObjectPropertiesViewOpen)
    {
        ImGui::Begin("Object Properties", &g_RuntimeEditorContext.ObjectPropertiesViewOpen, window_flags);
        if (m_SelectedEntity)
        {
            UpdateComponentList();
        }
        ImGui::End();
    }
}

void SceneLayer::UpdateEntityList()
{
    static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen;
    m_Scene->GetRegistry().each([&](auto entityId) {
        Entity entity(entityId, m_Scene.get());

        const std::string& name = entity.GetComponent<NameComponent>().Name;
        ImGuiTreeNodeFlags flags = base_flags | ((m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, "%s", name.c_str());
        if (ImGui::IsItemClicked())
        {
            m_SelectedEntity = entity;
        }

        if (opened)
        {
            ImGui::TreePop();
        }
    });
}

template<typename T>
struct PropertyField
{
    std::string Name;
    std::function<void(Entity&,T&)> OnUpdate;
};

template<typename T>
static std::vector<PropertyField<T>> UpdatePropertyPanel(Entity& entity, T& component){}

template<>
std::vector<PropertyField<TransformComponent>> UpdatePropertyPanel<TransformComponent>(Entity& entity, TransformComponent& component)
{
    return
    {
        {
            "Translate",
            [](Entity& entity, auto& component) {
                ImGui::DragFloat3("##Translation", (float*)&component.Translate, 0.01);

            }
        },
        {
            "Rotate",
            [](Entity& entity, auto& component) {
                glm::vec3 rotation = glm::degrees(component.Rotation);
                ImGui::DragFloat3("##Rotation", (float*)&rotation, 0.01);
                component.Rotation = glm::radians(rotation);
            }
        },
        {
            "Scale",
            [](Entity& entity, auto& component) {
                ImGui::DragFloat3("##Scale", (float*)&component.Scale, 1.0f, 0.01);
            }
        }
    };
}

template<>
std::vector<PropertyField<NameComponent>> UpdatePropertyPanel<NameComponent>(Entity& entity, NameComponent& component)
{
    return
    {
        {
            "Name",
            [](Entity& entity, auto& component) {
                static char buffer[64];
                std::copy(component.Name.begin(), component.Name.end(), buffer);
                buffer[component.Name.size()] = '\0';
                ImGui::PushItemWidth(-FLT_MIN);
                if (ImGui::InputText("##Entity_Name", buffer, sizeof(buffer)))
                {
                    component.Name = std::string(buffer);
                }
            }
        }
    };
}

template<>
std::vector<PropertyField<CameraComponent>> UpdatePropertyPanel<CameraComponent>(Entity& entity, CameraComponent& component)
{
    std::vector<PropertyField<CameraComponent>> fields =
    {
        {
            "Primary",
            [](Entity& entity, auto& component) {
                ImGui::Checkbox("Primary", &component.Primary);
            }
        },
        {
            "Projection",
            [](Entity& entity, auto& component) {
                struct CameraModeProperty
                {
                    Camera::Mode Mode;
                    std::string Name;
                };

                static std::array<CameraModeProperty, 2> Modes {{
                    { Camera::Mode::Perspective, std::string("Perspective") },
                    { Camera::Mode::Ortho, std::string("Orthographic") }
                }};

                CameraModeProperty currentMode = Modes[((uint8_t)component.Camera.GetMode())];
                if (ImGui::BeginCombo("##Projection", currentMode.Name.c_str()))
                {
                    for (const auto& mode : Modes)
                    {
                        bool isSelected = currentMode.Mode == mode.Mode;
                        if (ImGui::Selectable(mode.Name.c_str(), isSelected))
                        {
                            currentMode = mode;
                            component.Camera.SetMode(currentMode.Mode);
                        }

                        if (isSelected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }
            }
        }
    };

    if (component.Camera.GetMode() == Camera::Mode::Perspective)
    {
        fields.push_back({
            "FOV",
            [](Entity& entity, auto& component) {
                float value = glm::degrees(component.Camera.GetFOV());
                if (ImGui::DragFloat("##FOV", &value))
                {
                    component.Camera.SetFOV(glm::radians(value));
                }
            }
        });
    }
    else if (component.Camera.GetMode() == Camera::Mode::Ortho)
    {
        fields.push_back({
            "Zoom",
            [](Entity& entity, auto& component) {
                float value = component.Camera.GetZoom();
                if (ImGui::DragFloat("##Zoom", &value))
                {
                    component.Camera.SetZoom(value);
                }
            }
        });

    }

    return fields;
}

template<>
std::vector<PropertyField<PointLightComponent>> UpdatePropertyPanel<PointLightComponent>(Entity& entity, PointLightComponent& component)
{
    return
    {
        {
            "Color",
            [](Entity& entity, auto& component) {
                ImGui::ColorEdit3("##Color", (float*)&component.Color, 0.01);            }
        }
    };
}

template<>
std::vector<PropertyField<MeshComponent>> UpdatePropertyPanel<MeshComponent>(Entity& entity, MeshComponent& component)
{
    return {};
}


template<typename T>
static void UpdatePropertyPanelBase(const std::string& name, Entity& entity)
{
    ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImGui::Separator();
    const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
    bool opened = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, "%s", name.c_str());
    ImGui::PopStyleVar();

    ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
    if (ImGui::Button("X", ImVec2{ lineHeight, lineHeight }))
    {
        ImGui::OpenPopup("ComponentSettings");
    }

    bool removeComponent = false;
    if (ImGui::BeginPopup("ComponentSettings"))
    {
        if (ImGui::MenuItem("Remove component"))
            removeComponent = true;

        ImGui::EndPopup();
    }

    if (opened)
    {
        const auto& fields = UpdatePropertyPanel<T>(entity, entity.GetComponent<T>());

        if (ImGui::BeginTable("##TableName", 2))
        {
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 100.0f);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch);

            for (const auto& field : fields)
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", field.Name.c_str());

                ImGui::TableSetColumnIndex(1);
                ImGui::PushItemWidth(-FLT_MIN);
                field.OnUpdate(entity, entity.GetComponent<T>());
            }
            ImGui::EndTable();
        }

        ImGui::TreePop();
    }
}

void SceneLayer::UpdateComponentList()
{
    UpdatePropertyPanel<NameComponent>(m_SelectedEntity, m_SelectedEntity.GetComponent<NameComponent>());

    if (m_SelectedEntity.HasComponent<CameraComponent>())
    {
        UpdatePropertyPanelBase<CameraComponent>("Camera", m_SelectedEntity);
    }

    if (m_SelectedEntity.HasComponent<TransformComponent>())
    {
        UpdatePropertyPanelBase<TransformComponent>("Transform", m_SelectedEntity);
    }

    if (m_SelectedEntity.HasComponent<PointLightComponent>())
    {
        UpdatePropertyPanelBase<PointLightComponent>("Point light", m_SelectedEntity);
    }

    if (m_SelectedEntity.HasComponent<MeshComponent>())
    {
        UpdatePropertyPanelBase<MeshComponent>("Mesh", m_SelectedEntity);
    }


}

}
