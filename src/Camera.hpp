#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OGLSample
{

class Camera
{
public:
    Camera();

    void Update(float frameTime);
    void UpdateFrameTime(float frameTime);

    enum class CameraMovement{
        Forward, Backward,
        Left, Right
    };

    void Move(CameraMovement movement);
    void Rotate(glm::vec2 delta);

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    glm::vec3 GetPosition();

    void LookAt(glm::vec3 position = {5.0f, 5.0f, 5.0f}, glm::vec3 center = {0.0f, 0.0f, 0.0f}, glm::vec3 up = {0.0f, 1.0f, 0.0f});

private:
    glm::vec3 m_Position {0.f, 5.f, 5.f};
    float m_HorizontalAngle = 3.14f;
    float m_VerticalAngle = 0.0f;
    float m_InitialFoV = 45.0f;

    float m_Speed = 3.0f;
    float m_MouseSpeed = 0.001f;

    glm::mat4 m_ViewMatrix {1.f};
    glm::mat4 m_ProjectionMatrix {1.f};

    float m_FrameTime;
};

}

#endif
