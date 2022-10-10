#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace OGLSample
{

class Camera
{
public:
    Camera(Ref<Window>& window);
    void Update(float frameTime);

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    glm::vec3 GetPosition();

private:
    glm::vec3 m_Position {0.f, 0.f, 5.f};
    float m_HorizontalAngle = 3.14f;
    float m_VerticalAngle = 0.0f;
    float m_InitialFoV = 45.0f;

    float m_Speed = 3.0f;
    float m_MouseSpeed = 0.001f;

    glm::mat4 m_ViewMatrix {1.f};
    glm::mat4 m_ProjectionMatrix {1.f};

    Ref<Window> m_Window;
};

}

#endif