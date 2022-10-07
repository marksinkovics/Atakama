#include "Camera.hpp"
#include "Input.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include <iostream>

namespace OGLSample
{

Camera::Camera(Ref<Window>& window)
: m_Window(window)
{

}

glm::mat4 Camera::GetViewMatrix()
{
    return m_ViewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return m_ProjectionMatrix;
}

void Camera::Update(float frameTime)
{
	Input::MousePos mousePos = Input::IsMouseMoved(m_Window, GLFW_MOUSE_BUTTON_LEFT);

	m_HorizontalAngle += m_MouseSpeed * float(mousePos.X);
	m_VerticalAngle   += m_MouseSpeed * float(mousePos.Y);

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
	if (Input::IsKeyPressed(m_Window, GLFW_KEY_UP) || Input::IsKeyPressed(m_Window, GLFW_KEY_W)){
		m_Position += direction * frameTime * m_Speed;
	}
	// Move backward
	if (Input::IsKeyPressed(m_Window, GLFW_KEY_DOWN) || Input::IsKeyPressed(m_Window, GLFW_KEY_S)){
		m_Position -= direction * frameTime * m_Speed;
	}
	// Move right
	if (Input::IsKeyPressed(m_Window, GLFW_KEY_RIGHT) || Input::IsKeyPressed(m_Window, GLFW_KEY_D)){
		m_Position += right * frameTime * m_Speed;
	}
	// Move left
	if (Input::IsKeyPressed(m_Window, GLFW_KEY_LEFT) || Input::IsKeyPressed(m_Window, GLFW_KEY_A)){
		m_Position -= right * frameTime * m_Speed;
	}

    float FoV = m_InitialFoV;

    m_ProjectionMatrix = glm::perspective(glm::radians(FoV), (float)m_Window->GetRatio(), 0.1f, 100.0f);
    m_ViewMatrix = glm::lookAt(
        m_Position,               // Camera is here
        m_Position + direction,   // and looks here : at the same position, plus "direction"
        up                        // Head is up
    );
}

}
