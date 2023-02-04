#include "Camera.hpp"
#include "Atakama/Core/InputSystem.hpp"
#include "Atakama/Events/Event.hpp"
#include "Atakama/Events/EventDispatcher.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtx/vector_angle.hpp>

#include <cmath>
#include <iostream>

namespace Atakama
{

Camera::Camera(Mode mode)
{
    SetMode(mode);
}

glm::mat4 Camera::GetViewMatrix()
{
    glm::mat4 rotate = glm::mat4_cast(Transform.GetOrientation());
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), -Transform.Translate);
    return rotate * translate;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return m_ProjectionMatrix;
}

glm::vec3 Camera::GetPosition()
{
    return Transform.Translate;
}

Camera::Mode Camera::GetMode() const
{
    return m_Mode;
}

void Camera::SetMode(Mode mode)
{
    m_Mode = mode;

    if (m_Mode == Mode::Perspective)
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_InitialFoV), m_Ratio, 0.1f, 100.0f);
        return;
    }

    if (m_Mode == Mode::Ortho)
    {
        m_ProjectionMatrix = glm::ortho(-m_Ratio * m_Zoom, m_Ratio * m_Zoom, -m_Zoom, m_Zoom, -1.0f, 100.0f);
        return;
    }

    LOG_FATAL("Unknown camera mode.")
}

void Camera::Zoom(float offset)
{
    if (m_Mode == Mode::Perspective)
    {
        m_InitialFoV += offset;
        m_ProjectionMatrix = glm::perspective(glm::radians(m_InitialFoV), m_Ratio, 0.1f, 100.0f);
        return;
    }

    if (m_Mode == Mode::Ortho)
    {
        m_Zoom += offset;
        m_ProjectionMatrix = glm::ortho(-m_Ratio * m_Zoom, m_Ratio * m_Zoom, -m_Zoom, m_Zoom, -1.0f, 100.0f);
        return;
    }

    LOG_FATAL("Unknown camera mode.")
}

void Camera::Resize(uint32_t width, uint32_t height)
{
    m_Viewport = { width, height };
    m_Ratio = (float)m_Viewport.x / (float)m_Viewport.y;

    if (m_Mode == Mode::Perspective)
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_InitialFoV), m_Ratio, 0.1f, 100.0f);
        return;
    }

    if (m_Mode == Mode::Ortho)
    {
        m_ProjectionMatrix = glm::ortho(-m_Ratio * m_Zoom, m_Ratio * m_Zoom, -m_Zoom, m_Zoom, -1.0f, 100.0f);
        return;
    }

    LOG_FATAL("Unknown camera mode.")
}

}
