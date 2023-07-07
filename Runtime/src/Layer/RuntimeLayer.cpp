#include "RuntimeLayer.hpp"

#include "RuntimeApplication.hpp"

#include <Atakama/Core/InputSystem.hpp>


#include <Atakama/Scene/Scene.hpp>
#include <Atakama/Scene/Entity.hpp>
#include <Atakama/Engine/Engine.hpp>
#include <Atakama/Engine/Camera.hpp>
#include <Atakama/Engine/CameraSystem.hpp>

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

namespace Atakama::Runtime
{

RuntimeLayer::RuntimeLayer()
    : Layer("Runtime Layer")
{
    m_Application = g_RuntimeGlobalContext.m_Application;
    m_InputSystem = g_RuntimeGlobalContext.m_InputSystem;
    m_CameraSystem = g_RuntimeGlobalContext.m_CameraSystem;
}

void RuntimeLayer::OnAttach()
{
}

void RuntimeLayer::OnDetach()
{
}

void RuntimeLayer::OnUpdate(float ts)
{
    Entity cameraEntity = g_RuntimeGlobalContext.m_Engine->GetScene()->GetPrimaryCameraEntity();


    if (m_InputSystem->IsKeyPressed(GLFW_KEY_ESCAPE) && m_InputSystem->GetFocusMode() == true) 
    {
        m_InputSystem->SetFocusMode(false);
    }

    if (m_InputSystem->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && m_InputSystem->GetFocusMode() == false)
    {
        m_InputSystem->SetFocusMode(true);
    }

    if (m_InputSystem->GetFocusMode() == true)
    {
        glm::dvec2 delta = m_InputSystem->GetMouseDelta();
        m_CameraSystem->Rotate(cameraEntity, -delta, ts);
    }
        
    if (m_InputSystem->IsKeyPressed(GLFW_KEY_UP) || m_InputSystem->IsKeyPressed(GLFW_KEY_W))
    {
        m_CameraSystem->Move(cameraEntity, CameraSystem::Movement::Forward, ts);
    }

    if (m_InputSystem->IsKeyPressed(GLFW_KEY_DOWN) || m_InputSystem->IsKeyPressed(GLFW_KEY_S))
    {
        m_CameraSystem->Move(cameraEntity, CameraSystem::Movement::Backward, ts);
    }

    if (m_InputSystem->IsKeyPressed(GLFW_KEY_RIGHT) || m_InputSystem->IsKeyPressed(GLFW_KEY_D))
    {
        m_CameraSystem->Move(cameraEntity, CameraSystem::Movement::Right, ts);
    }

    if (m_InputSystem->IsKeyPressed(GLFW_KEY_LEFT) || m_InputSystem->IsKeyPressed(GLFW_KEY_A))
    {
        m_CameraSystem->Move(cameraEntity, CameraSystem::Movement::Left, ts);
    }

    if (m_InputSystem->IsKeyPressed(GLFW_KEY_Q))
    {
        m_CameraSystem->Move(cameraEntity, CameraSystem::Movement::Down, ts);
    }

    if (m_InputSystem->IsKeyPressed(GLFW_KEY_E))
    {
        m_CameraSystem->Move(cameraEntity, CameraSystem::Movement::Up, ts);
    }
}

void RuntimeLayer::OnUpdateUI(float ts)
{

}

}
