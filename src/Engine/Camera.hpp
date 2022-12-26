#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Window.hpp"

namespace OGLSample
{


enum class Movement;
class MouseScrolledEvent;
class WindowResizeEvent;

class Camera
{

public:
    enum class Mode
    {
        Perspective, Ortho
    };
public:
    Camera(Mode mode);
    virtual ~Camera() = default;
    
    virtual void Update(float frameTime);
    virtual void Move(Movement movement, float frameTime);
    virtual void Rotate(glm::vec2 delta, float frameTime, bool constrainPitch = true);
    virtual void LookAt(glm::vec3 position, glm::vec3 center = {0.0f, 0.0f, 0.0f}, glm::vec3 up = {0.0f, 1.0f, 0.0f});

    virtual glm::mat4 GetViewMatrix();
    virtual glm::mat4 GetProjectionMatrix();
    virtual glm::vec3 GetPosition();
    
    virtual Mode GetMode() const;
    virtual void SetMode(Mode mode);
    
    virtual bool OnMouseScrollEvent(MouseScrolledEvent& event);
    virtual bool OnWindowResize(WindowResizeEvent& event);
protected:
    glm::vec3 m_Position {0.f, 5.f, 5.f};

    float m_Speed = 3.0f;
    float m_MouseSpeed = 0.001f;
    
    float m_Yaw = 3.14f; // Horizontal angle
    float m_Pitch = 0.0f; // Vertical angle
    float m_InitialFoV = 45.0f; // Perspective only
    float m_Zoom = 2.0f; // Ortho only
    
    glm::vec3 m_Direction;
    glm::vec3 m_Right;
    glm::vec3 m_Up;
    glm::vec3 m_WorldUp;

    glm::mat4 m_ViewMatrix {1.f};
    glm::mat4 m_ProjectionMatrix {1.f};
    
    Mode m_Mode;
};

}

#endif
