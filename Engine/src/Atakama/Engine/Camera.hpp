#ifndef ATAKAMA_CAMERA_HPP
#define ATAKAMA_CAMERA_HPP

#include "Atakama/Scene/Components/TransformComponent.hpp"

namespace Atakama
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
    Camera();
    Camera(Mode mode);
    Camera(Camera&) = default;
    virtual ~Camera() = default;

    virtual glm::mat4 GetViewMatrix();
    virtual glm::mat4 GetProjectionMatrix();
    virtual glm::vec3 GetPosition();

    virtual Mode GetMode() const;
    virtual void SetMode(Mode mode);
    
    virtual void Resize(uint32_t width, uint32_t height);
    virtual void Zoom(float offset);

    TransformComponent Transform;
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
