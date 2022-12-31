#include "Camera.hpp"
#include "InputSystem.hpp"
#include "Events/Event.hpp"
#include "Events/WindowEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/EventDispatcher.hpp"
#include "Window.hpp"


#include <GLFW/glfw3.h>
#include <glm/gtx/vector_angle.hpp>

#include <cmath>
#include <iostream>

namespace OGLSample
{

Camera::Camera(Mode mode)
{
    SetMode(mode);
    
    g_RuntimeGlobalContext.m_Dispatcher->subscribe<MouseScrolledEvent>(std::bind(&Camera::OnMouseScrollEvent, this, std::placeholders::_1));
    g_RuntimeGlobalContext.m_Dispatcher->subscribe<WindowResizeEvent>(std::bind(&Camera::OnWindowResize, this, std::placeholders::_1));
}

void Camera::Update(float frameTime)
{
    Ref<InputSystem> inputSystem = g_RuntimeGlobalContext.m_InputSystem;
    if (inputSystem->IsKeyPressed(GLFW_KEY_X)){
        LookAt(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        return;
    }

    if (inputSystem->IsKeyPressed(GLFW_KEY_Y)){
        LookAt(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        return;
    }

    if (inputSystem->IsKeyPressed(GLFW_KEY_Z)){
        LookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        return;
    }


    glm::dvec2 mousePos = {0.f, 0.f};
    
    if (inputSystem->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) || inputSystem->GetFocusMode())
    {
        mousePos = inputSystem->GetMouseDelta();
        Rotate(mousePos, frameTime);
    }

    Move(inputSystem->GetMovement(), frameTime);
}

void Camera::Move(Movement movement, float frameTime)
{
    m_Transform.Move(movement, m_Speed * frameTime);
}

void Camera::Rotate(glm::vec2 delta, float frameTime, bool constrainPitch)
{
    float yaw   = m_Transform.GetYaw() + delta.x * m_MouseSpeed;
    float pitch = m_Transform.GetPitch() + delta.y * m_MouseSpeed;

    if (constrainPitch) {
        if (pitch > 89.0f)
        {
            pitch = 89.0f;
        }

        if (pitch < -89.0f)
        {
            pitch = -89.0f;
        }
    }

    m_Transform.SetYaw(yaw);
    m_Transform.SetPitch(pitch);

}

// Note: https://stackoverflow.com/a/33790309/5218198
void Camera::LookAt(const glm::vec3& cameraPostion, const glm::vec3& cameraTarget)
{
    m_Transform.SetTranslate(cameraPostion);
    glm::vec3 direction = glm::normalize(cameraTarget - cameraPostion);

    float yaw = std::atan2(direction.x, -direction.z);
    m_Transform.SetYaw(yaw);

    float pitch = glm::asin(-direction.y);
    m_Transform.SetPitch(pitch);
}


glm::mat4 Camera::GetViewMatrix()
{
    return m_Transform.GetMat4();
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return m_ProjectionMatrix;
}

glm::vec3 Camera::GetPosition()
{
	return m_Transform.GetTranslate();
}

Camera::Mode Camera::GetMode() const
{
    return m_Mode;
}

void Camera::SetMode(Mode mode)
{
    Ref<Window> window = g_RuntimeGlobalContext.m_Window;
    m_Mode = mode;
    
    switch(mode)
    {
        case Mode::Perspective:
        {
            m_ProjectionMatrix = glm::perspective(glm::radians(m_InitialFoV), (float)window->GetRatio(), 0.1f, 100.0f);
            break;
        }
        case Mode::Ortho:
        {
            float aspectRatio = window->GetRatio();
            m_ProjectionMatrix = glm::ortho(-aspectRatio * m_Zoom, aspectRatio * m_Zoom, -m_Zoom, m_Zoom, -1.0f, 100.0f);
            break;
        }
        default:
            LOG_FATAL("Unknown camera mode.")
    }
}

bool Camera::OnMouseScrollEvent(MouseScrolledEvent& event)
{
    Ref<Window> window = g_RuntimeGlobalContext.m_Window;
    switch(m_Mode)
    {
        case Mode::Perspective:
        {
            m_InitialFoV += event.GetYOffset() * 0.1f;
            m_ProjectionMatrix = glm::perspective(glm::radians(m_InitialFoV), (float)window->GetRatio(), 0.1f, 100.0f);
            break;
        }
        case Mode::Ortho:
        {
            m_Zoom += event.GetYOffset() * 0.1f;
            float aspectRatio = window->GetRatio();
            m_ProjectionMatrix = glm::ortho(-aspectRatio * m_Zoom, aspectRatio * m_Zoom, -m_Zoom, m_Zoom, -1.0f, 100.0f);
            break;
        }
        default:
            LOG_FATAL("Unknown camera mode.")
    }
    return false;
}

bool Camera::OnWindowResize(WindowResizeEvent& event)
{
    Ref<Window> window = g_RuntimeGlobalContext.m_Window;
    switch(m_Mode)
    {
        case Mode::Perspective:
        {
            m_ProjectionMatrix = glm::perspective(glm::radians(m_InitialFoV), (float)window->GetRatio(), 0.1f, 100.0f);
            break;
        }
        case Mode::Ortho:
        {
            float aspectRatio = window->GetRatio();
            m_ProjectionMatrix = glm::ortho(-aspectRatio * m_Zoom, aspectRatio * m_Zoom, -m_Zoom, m_Zoom, -1.0f, 100.0f);
            break;
        }
        default:
            LOG_FATAL("Unknown camera mode.")
    }

    return false;
}

}
