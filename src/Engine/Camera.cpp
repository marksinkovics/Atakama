#include "Camera.hpp"
#include "InputSystem.hpp"
#include "Events/Event.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/EventDispatcher.hpp"

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
}

void Camera::Update(float frameTime)
{
    Ref<InputSystem> inputSystem = g_RuntimeGlobalContext.m_InputSystem;
    if (inputSystem->IsKeyPressed(GLFW_KEY_X))
    {
        LookAt(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        return;
    }

    if (inputSystem->IsKeyPressed(GLFW_KEY_Y))
    {
        LookAt(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        return;
    }

    if (inputSystem->IsKeyPressed(GLFW_KEY_Z))
    {
        LookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        return;
    }

    if (inputSystem->IsKeyPressed(GLFW_KEY_R))
    {
        LookAt(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        return;
    }

    glm::dvec2 mousePos = {0.f, 0.f};
    
    if (inputSystem->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) || inputSystem->GetFocusMode())
    {
        mousePos = inputSystem->GetMouseDelta();
        Rotate(mousePos, frameTime);
    }

    Move(inputSystem->GetMovement(), frameTime);
    UpdateVectors();
}

void Camera::Move(Movement movement, float frameTime)
{
    float value = m_Speed * frameTime;

    if (movement == Movement::Forward)
    {
        m_Position += m_Forward * value;
    }

    if (movement == Movement::Backward)
    {
        m_Position -= m_Forward * value;
    }

    if (movement == Movement::Right)
    {
        m_Position += m_Right * value;
    }

    if (movement == Movement::Left)
    {
        m_Position -= m_Right * value;
    }

    if (movement == Movement::Up)
    {
        m_Position += m_Up * value;
    }

    if (movement == Movement::Down)
    {
        m_Position -= m_Up * value;
    }
}

void Camera::Rotate(glm::vec2 delta, float frameTime, bool constrainPitch)
{
    float yaw   = m_Yaw + delta.x * m_MouseSpeed;
    float pitch = m_Pitch + delta.y * m_MouseSpeed;

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

    m_Yaw = yaw;
    m_Pitch = pitch;

    UpdateVectors();
}

// Note: https://stackoverflow.com/a/33790309/5218198
void Camera::LookAt(const glm::vec3& cameraPostion, const glm::vec3& cameraTarget)
{
    m_Position = cameraPostion;
    glm::vec3 direction = glm::normalize(cameraTarget - cameraPostion);

    float yaw = std::atan2(direction.x, -direction.z);
    m_Yaw = yaw;

    float pitch = glm::asin(-direction.y);
    m_Pitch = pitch;

    UpdateVectors();
}

void Camera::UpdateVectors()
{
    m_Forward = glm::rotate(glm::inverse(m_Orientation), glm::vec3(0.0, 0.0, -1.0));
    m_Right = glm::rotate(glm::inverse(m_Orientation), glm::vec3(1.0, 0.0, 0.0));
    m_Up = glm::vec3(0.0, 1.0, 0.0);
}

glm::mat4 Camera::GetViewMatrix()
{
    glm::quat qPitch = glm::angleAxis(m_Pitch, glm::vec3(1.f, 0.f, 0.f));
    glm::quat qYaw = glm::angleAxis(m_Yaw, glm::vec3(0.f, 1.f, 0.f));
    // omit roll
    m_Orientation = glm::normalize(qPitch * qYaw);
    glm::mat4 rotate = glm::mat4_cast(m_Orientation);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), -m_Position);
    return rotate * translate;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return m_ProjectionMatrix;
}

glm::vec3 Camera::GetPosition()
{
    return m_Position;
}

Camera::Mode Camera::GetMode() const
{
    return m_Mode;
}

void Camera::SetMode(Mode mode)
{
    m_Mode = mode;
    
    switch(mode)
    {
        case Mode::Perspective:
        {
            m_ProjectionMatrix = glm::perspective(glm::radians(m_InitialFoV), m_Ratio, 0.1f, 100.0f);
            break;
        }
        case Mode::Ortho:
        {
            m_ProjectionMatrix = glm::ortho(-m_Ratio * m_Zoom, m_Ratio * m_Zoom, -m_Zoom, m_Zoom, -1.0f, 100.0f);
            break;
        }
        default:
            LOG_FATAL("Unknown camera mode.")
    }
}

bool Camera::OnMouseScrollEvent(MouseScrolledEvent& event)
{
    switch(m_Mode)
    {
        case Mode::Perspective:
        {
            m_InitialFoV += event.GetYOffset() * 0.1f;
            m_ProjectionMatrix = glm::perspective(glm::radians(m_InitialFoV), m_Ratio, 0.1f, 100.0f);
            break;
        }
        case Mode::Ortho:
        {
            m_Zoom += event.GetYOffset() * 0.1f;
            m_ProjectionMatrix = glm::ortho(-m_Ratio * m_Zoom, m_Ratio * m_Zoom, -m_Zoom, m_Zoom, -1.0f, 100.0f);
            break;
        }
        default:
            LOG_FATAL("Unknown camera mode.")
    }
    return false;
}

void Camera::Resize(uint32_t width, uint32_t height)
{
    m_Viewport = { width, height };
    m_Ratio = (float)m_Viewport.x / (float)m_Viewport.y;

    switch(m_Mode)
    {
        case Mode::Perspective:
        {
            m_ProjectionMatrix = glm::perspective(glm::radians(m_InitialFoV), m_Ratio, 0.1f, 100.0f);
            break;
        }
        case Mode::Ortho:
        {
            m_ProjectionMatrix = glm::ortho(-m_Ratio * m_Zoom, m_Ratio * m_Zoom, -m_Zoom, m_Zoom, -1.0f, 100.0f);
            break;
        }
        default:
            LOG_FATAL("Unknown camera mode.")
    }
}

}
