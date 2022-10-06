#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

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
    double mouseX, mouseY;
	glfwGetCursorPos(m_Window->GetWindow(), &mouseX, &mouseY);
    glfwSetCursorPos(m_Window->GetWindow(), m_Window->GetWidth()/2, m_Window->GetHeight()/2);

	// Compute new orientation
	m_HorizontalAngle += m_MouseSpeed * float(m_Window->GetWidth()/2  - mouseX);
	m_VerticalAngle   += m_MouseSpeed * float(m_Window->GetHeight()/2 - mouseY);

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
	if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_UP) == GLFW_PRESS){
		m_Position += direction * frameTime * m_Speed;
	}
	// Move backward
	if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_DOWN ) == GLFW_PRESS){
		m_Position -= direction * frameTime * m_Speed;
	}
	// Strafe right
	if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_RIGHT ) == GLFW_PRESS){
		m_Position += right * frameTime * m_Speed;
	}
	// Strafe left
	if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_LEFT ) == GLFW_PRESS){
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
