#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Math/Transform.hpp"

namespace OGLSample
{

enum class Movement;
class WindowResizeEvent;
class Transform;
class CameraSystem;

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

    virtual glm::mat4 GetViewMatrix();
    virtual glm::mat4 GetProjectionMatrix();
    virtual glm::vec3 GetPosition();

    virtual Mode GetMode() const;
    virtual void SetMode(Mode mode);
    
    virtual void Resize(uint32_t width, uint32_t height);
    virtual void Zoom(float offset);

    Transform Transform;
protected:
    float m_InitialFoV = 45.0f; // Perspective only
    float m_Zoom = 2.0f; // Ortho only

    glm::mat4 m_ProjectionMatrix {1.f};
    
    Mode m_Mode;

    float m_Ratio;
    glm::uvec2 m_Viewport;

    friend CameraSystem;
};

}

#endif
