#include "Camera.hpp"
#include "InputSystem.hpp"
#include "Events/Event.hpp"
#include "Events/WindowEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/EventDispatcher.hpp"

#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

namespace OGLSample
{

Camera::Camera(Mode mode)
: m_WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)), m_Position({0.0f, 0.0f, 0.0f})
{
    SetMode(mode);
    
    g_RuntimeGlobalContext.m_Dispatcher->subscribe<MouseScrolledEvent>(std::bind(&Camera::OnMouseScrollEvent, this, std::placeholders::_1));
    g_RuntimeGlobalContext.m_Dispatcher->subscribe<WindowResizeEvent>(std::bind(&Camera::OnWindowResize, this, std::placeholders::_1));
}

void Camera::Update(float frameTime)
{
    Ref<InputSystem> inputSystem = g_RuntimeGlobalContext.m_InputSystem;
    glm::dvec2 mousePos = {0.f, 0.f};
    
    if (inputSystem->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) || inputSystem->GetFocusMode())
    {
        mousePos = inputSystem->GetMouseDelta();
    }
    
    Rotate(mousePos, frameTime);
    Move(inputSystem->GetMovement(), frameTime);

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction = glm::vec3(
        cos(m_Pitch) * sin(m_Yaw),
        sin(m_Pitch),
        cos(m_Pitch) * cos(m_Yaw)
    );
    
    m_Direction = glm::normalize(direction);
    m_Right = glm::normalize(glm::cross(m_Direction, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Direction));

    m_ViewMatrix = glm::lookAt(
        m_Position,                 // Camera is here
        m_Position + m_Direction,   // and looks here
        m_Up                        // Head is up
    );
}

void Camera::Move(Movement movement, float frameTime)
{
    // Move forward
    if (movement == Movement::Forward){
        m_Position += m_Direction * frameTime * m_Speed;
    }
    // Move backward
    if (movement == Movement::Backward){
        m_Position -= m_Direction * frameTime * m_Speed;
    }
    // Move right
    if (movement == Movement::Right){
        m_Position += m_Right * frameTime * m_Speed;
    }
    // Move left
    if (movement == Movement::Left){
        m_Position -= m_Right * frameTime * m_Speed;
    }
    
    if (movement == Movement::Up){
        m_Position += m_Up * frameTime * m_Speed;
    }
    
    if (movement == Movement::Down){
        m_Position -= m_Up * frameTime * m_Speed;
    }
}

void Camera::Rotate(glm::vec2 delta, float frameTime, bool constrainPitch)
{
    m_Yaw   += delta.x * m_MouseSpeed;
    m_Pitch += delta.y * m_MouseSpeed;
    
    if (constrainPitch) {
        if (m_Pitch > 89.0f)
        {
            m_Pitch = 89.0f;
        }
        
        if (m_Pitch < -89.0f)
        {
            m_Pitch = -89.0f;
        }
    }
}

void Camera::LookAt(glm::vec3 position, glm::vec3 center, glm::vec3 up)
{
    m_Position = position;
    m_Up = up;
    m_WorldUp = up;
    m_ViewMatrix = glm::lookAt(m_Position, center, up);

    glm::vec3 direction = m_Position - center;

    m_Pitch = -glm::asin(direction.y / glm::distance(center, m_Position));
    m_Yaw = glm::pi<float>() + glm::atan(direction.x, direction.z);
}


glm::mat4 Camera::GetViewMatrix()
{
    return m_ViewMatrix;
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
