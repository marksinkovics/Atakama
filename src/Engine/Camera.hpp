#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Math/Transform.hpp"

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
    virtual void LookAt(const glm::vec3& cameraPostion, const glm::vec3& cameraTarget);

    virtual glm::mat4 GetViewMatrix();
    virtual glm::mat4 GetProjectionMatrix();
    virtual glm::vec3 GetPosition();
    
    virtual Mode GetMode() const;
    virtual void SetMode(Mode mode);
    
    virtual bool OnMouseScrollEvent(MouseScrolledEvent& event);
    virtual void Resize(uint32_t width, uint32_t height);
protected:
    Transform m_Transform;

    float m_Speed = 3.0f;
    float m_MouseSpeed = 0.001f;

    float m_InitialFoV = 45.0f; // Perspective only
    float m_Zoom = 2.0f; // Ortho only

    glm::mat4 m_ProjectionMatrix {1.f};
    
    Mode m_Mode;

    float m_Ratio;
    glm::uvec2 m_Viewport;
};

}

#endif
