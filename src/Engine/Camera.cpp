#include "Camera.hpp"
#include "InputSystem.hpp"

#include <cmath>

#include <iostream>

namespace OGLSample
{

Camera::Camera()
{
    Ref<Window> window = g_RuntimeGlobalContext.m_Window;
    m_ProjectionMatrix = glm::perspective(glm::radians(m_InitialFoV), (float)window->GetRatio(), 0.1f, 100.0f);
    //m_ProjectionMatrix = glm::ortho(0.0f, (float)m_Window->GetWidth(), 0.0f, (float)m_Window->GetHeight(), 0.1f, 100.0f);
}

void Camera::LookAt(glm::vec3 position, glm::vec3 center, glm::vec3 up)
{
    m_Position = position;
    m_ViewMatrix = glm::lookAt(m_Position, center, up);

    glm::vec3 direction = m_Position - center;

    float length = glm::distance(center, m_Position);
    float verticalAngle = -glm::asin(direction.y / length);
    m_VerticalAngle = verticalAngle;

    float horizontalAngle = glm::pi<float>() + glm::atan(direction.x, direction.z);
    m_HorizontalAngle = horizontalAngle;
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

void Camera::UpdateFrameTime(float frameTime)
{
	m_FrameTime = frameTime;
}

void Camera::Update(float frameTime)
{
    Ref<InputSystem> inputSystem = g_RuntimeGlobalContext.m_InputSystem;
    glm::dvec2 mousePos = {0.f, 0.f};
    
    if (inputSystem->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) || inputSystem->GetFocusMode())
    {
        mousePos = inputSystem->GetMouseDelta();
    }
    
    m_HorizontalAngle += m_MouseSpeed * float(mousePos.x);
	m_VerticalAngle   += m_MouseSpeed * float(mousePos.y);

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction = glm::vec3(
		cos(m_VerticalAngle) * sin(m_HorizontalAngle),
		sin(m_VerticalAngle),
		cos(m_VerticalAngle) * cos(m_HorizontalAngle)
	);

    // Right vector
	glm::vec3 right(
		sin(m_HorizontalAngle - glm::half_pi<float>()),
		0,
		cos(m_HorizontalAngle - glm::half_pi<float>())
	);

    // Up vector (perpendicular)
	glm::vec3 up = glm::cross(right, direction);

    // Move forward
	if (inputSystem->IsKeyPressed(GLFW_KEY_UP) || inputSystem->IsKeyPressed(GLFW_KEY_W))
    {
		m_Position += direction * frameTime * m_Speed;
	}
	// Move backward
	if (inputSystem->IsKeyPressed(GLFW_KEY_DOWN) || inputSystem->IsKeyPressed(GLFW_KEY_S))
    {
		m_Position -= direction * frameTime * m_Speed;
	}
	// Move right
	if (inputSystem->IsKeyPressed(GLFW_KEY_RIGHT) || inputSystem->IsKeyPressed(GLFW_KEY_D))
    {
		m_Position += right * frameTime * m_Speed;
	}
	// Move left
	if (inputSystem->IsKeyPressed(GLFW_KEY_LEFT) || inputSystem->IsKeyPressed(GLFW_KEY_A))
    {
		m_Position -= right * frameTime * m_Speed;
	}

    float FoV = m_InitialFoV;

    m_ViewMatrix = glm::lookAt(
        m_Position,               // Camera is here
        m_Position + direction,   // and looks here
        up                        // Head is up
    );
}

void Camera::Move(CameraMovement movement)
{
	glm::vec3 direction = glm::vec3(
		cos(m_VerticalAngle) * sin(m_HorizontalAngle),
		sin(m_VerticalAngle),
		cos(m_VerticalAngle) * cos(m_HorizontalAngle)
	);

	glm::vec3 right(
		sin(m_HorizontalAngle - glm::half_pi<float>()),
		0,
		cos(m_HorizontalAngle - glm::half_pi<float>())
	);

    // Up vector (perpendicular)
	glm::vec3 up = glm::cross(right, direction);

    // Move forward
	if (movement == CameraMovement::Forward){
		m_Position += direction * m_FrameTime * m_Speed;
	}
	// Move backward
	if (movement == CameraMovement::Backward){
		m_Position -= direction * m_FrameTime * m_Speed;
	}
	// Move right
	if (movement == CameraMovement::Right){
		m_Position += right * m_FrameTime * m_Speed;
	}
	// Move left
	if (movement == CameraMovement::Left){
		m_Position -= right * m_FrameTime * m_Speed;
	}



    m_ViewMatrix = glm::lookAt(
        m_Position,               // Camera is here
        m_Position + direction,   // and looks here
        up                        // Head is up
    );

}

void Camera::Rotate(glm::vec2 delta)
{
	m_HorizontalAngle += m_MouseSpeed * float(delta.x);
	m_VerticalAngle   += m_MouseSpeed * float(delta.y);

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction = glm::vec3(
		cos(m_VerticalAngle) * sin(m_HorizontalAngle),
		sin(m_VerticalAngle),
		cos(m_VerticalAngle) * cos(m_HorizontalAngle)
	);

    // Right vector
	glm::vec3 right(
		sin(m_HorizontalAngle - glm::half_pi<float>()),
		0,
		cos(m_HorizontalAngle - glm::half_pi<float>())
	);

    // Up vector (perpendicular)
	glm::vec3 up = glm::cross(right, direction);

    m_ViewMatrix = glm::lookAt(
        m_Position,               // Camera is here
        m_Position + direction,   // and looks here
        up                        // Head is up
    );
}



}
