#include "CameraSystem.hpp"

#include "Camera.hpp"

#include "Atakama/Core/InputSystem.hpp"
#include "Atakama/Scene/Entity.hpp"
#include "Atakama/Scene/Components/Components.hpp"
#include "Atakama/Scene/Components/TransformComponent.hpp"

namespace Atakama
{

void CameraSystem::Move(Entity cameraEntity, Movement movement, float ts)
{
    auto& transform = cameraEntity.GetComponent<TransformComponent>();

    float value = m_Speed * ts;

    if (movement == Movement::Forward)
    {
        transform.Translate += GetForward(cameraEntity) * value;
    }

    if (movement == Movement::Backward)
    {
        transform.Translate -= GetForward(cameraEntity) * value;
    }

    if (movement == Movement::Right)
    {
        transform.Translate += GetRight(cameraEntity) * value;
    }

    if (movement == Movement::Left)
    {
        transform.Translate -= GetRight(cameraEntity) * value;
    }

    if (movement == Movement::Up)
    {
        transform.Translate += GetUp(cameraEntity) * value;
    }

    if (movement == Movement::Down)
    {
        transform.Translate -= GetUp(cameraEntity) * value;
    }
}

void CameraSystem::Rotate(Entity cameraEntity, glm::vec2 delta, float ts, bool constrainPitch)
{
    auto& transform = cameraEntity.GetComponent<TransformComponent>();

    float yaw   = transform.Rotation.y + delta.x * m_MouseSpeed;
    float pitch = transform.Rotation.x + delta.y * m_MouseSpeed;

    if (constrainPitch)
    {
        if (pitch > 89.0f)
        {
            pitch = 89.0f;
        }

        if (pitch < -89.0f)
        {
            pitch = -89.0f;
        }
    }
    transform.Rotation.x = pitch;
    transform.Rotation.y = yaw;
}

void CameraSystem::LookAt(Entity cameraEntity, const glm::vec3& cameraPostion, const glm::vec3& cameraTarget)
{
    auto& transform = cameraEntity.GetComponent<TransformComponent>();

    transform.Translate = cameraPostion;
    glm::vec3 direction = glm::normalize(cameraTarget - cameraPostion);

    float yaw = std::atan2(direction.x, -direction.z);
    transform.Rotation.y = yaw;

    float pitch = glm::asin(-direction.y);
    transform.Rotation.x = pitch;
}

glm::vec3 CameraSystem::GetForward(Entity cameraEntity)
{
    auto& transform = cameraEntity.GetComponent<TransformComponent>();
    return glm::rotate(glm::inverse(transform.GetOrientation()), glm::vec3(0.0, 0.0, -1.0));
}

glm::vec3 CameraSystem::GetRight(Entity cameraEntity)
{
    auto& transform = cameraEntity.GetComponent<TransformComponent>();
    return glm::rotate(glm::inverse(transform.GetOrientation()), glm::vec3(1.0, 0.0, 0.0));
}

glm::vec3 CameraSystem::GetUp(Entity cameraEntity)
{
    return glm::vec3(0.0, 1.0, 0.0);
}

}
