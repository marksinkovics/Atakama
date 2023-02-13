#ifndef ATAKAMA_CAMERA_HPP
#define ATAKAMA_CAMERA_HPP

#include "Atakama/Scene/Components/TransformComponent.hpp"

#include <array>

namespace Atakama
{

enum class Movement;
class WindowResizeEvent;
class Transform;
class CameraSystem;

class Camera
{

public:
    enum class Mode: uint8_t
    {
        Perspective = 0, Ortho
    };
    constexpr static const std::array<Mode, 2> AllModes { Mode::Perspective, Mode::Ortho };
public:
    Camera();
    Camera(Mode mode);
    Camera(Camera&) = default;
    virtual ~Camera() = default;

    virtual glm::mat4 GetViewMatrix(TransformComponent& transform);
    virtual glm::mat4 GetProjectionMatrix();

    virtual Mode GetMode() const;
    virtual void SetMode(Mode mode);
    
    virtual void Resize(uint32_t width, uint32_t height);
    virtual void Zoom(float offset);

    float GetFOV() { return m_FOV; }
    void SetFOV(float value) { m_FOV = value; }

    float GetZoom() { return m_Zoom; }
    void SetZoom(float value) { m_Zoom = value; }

protected:
    float m_FOV = glm::radians(45.0f); // Perspective only
    float m_Zoom = 2.0f; // Ortho only

    glm::mat4 m_ProjectionMatrix {1.f};
    
    Mode m_Mode;

    float m_Ratio { 1.f };
    glm::uvec2 m_Viewport;

    friend CameraSystem;
};

}

#endif
