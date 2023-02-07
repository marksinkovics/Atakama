#include "SceneLayer.hpp"

#include <Atakama/Engine/Engine.hpp>
#include <Atakama/Scene/Scene.hpp>

#include <imgui.h>

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
    ImGui::Begin("Scene");
    ImGui::DragFloat3("Light position", (float*)&m_Scene->GetLight()->GetPositionRef(), 0.01);
    ImGui::ColorEdit3("Light color", (float*)&m_Scene->GetLight()->GetColorRef());
    ImGui::End();
}

}
