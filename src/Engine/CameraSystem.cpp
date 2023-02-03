#include "CameraSystem.hpp"
#include "Camera.hpp"
#include "InputSystem.hpp"

#include <GLFW/glfw3.h>

namespace Atakama
{

void CameraSystem::Update(Ref<Camera>& camera, float ts)
{
    Ref<InputSystem> inputSystem = g_RuntimeGlobalContext.m_InputSystem;
    if (inputSystem->IsKeyPressed(GLFW_KEY_X))
    {
        LookAt(camera, glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        return;
    }

    if (inputSystem->IsKeyPressed(GLFW_KEY_Y))
    {
        LookAt(camera, glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        return;
    }

    if (inputSystem->IsKeyPressed(GLFW_KEY_Z))
    {
        LookAt(camera, glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        return;
    }

    if (inputSystem->IsKeyPressed(GLFW_KEY_R))
    {
        LookAt(camera, glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        return;
    }

    glm::dvec2 mousePos = {0.f, 0.f};

    if (inputSystem->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) || inputSystem->GetFocusMode())
    {
        mousePos = inputSystem->GetMouseDelta();
        Rotate(camera, mousePos, ts);
    }

    Move(camera, inputSystem->GetMovement(), ts);
}

void CameraSystem::Move(Ref<Camera>& camera, Movement movement, float ts)
{
    float value = m_Speed * ts;

    if (movement == Movement::Forward)
    {
        camera->Transform.Translate += GetForward(camera) * value;
    }

    if (movement == Movement::Backward)
    {
        camera->Transform.Translate -= GetForward(camera) * value;
    }

    if (movement == Movement::Right)
    {
        camera->Transform.Translate += GetRight(camera) * value;
    }

    if (movement == Movement::Left)
    {
        camera->Transform.Translate -= GetRight(camera) * value;
    }

    if (movement == Movement::Up)
    {
        camera->Transform.Translate += GetUp(camera) * value;
    }

    if (movement == Movement::Down)
    {
        camera->Transform.Translate -= GetUp(camera) * value;
    }
}

void CameraSystem::Rotate(Ref<Camera>& camera, glm::vec2 delta, float ts, bool constrainPitch)
{
    float yaw   = camera->Transform.Rotation.y + delta.x * m_MouseSpeed;
    float pitch = camera->Transform.Rotation.x + delta.y * m_MouseSpeed;

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
    camera->Transform.Rotation.x = pitch;
    camera->Transform.Rotation.y = yaw;
}

void CameraSystem::LookAt(Ref<Camera>& camera, const glm::vec3& cameraPostion, const glm::vec3& cameraTarget)
{
    camera->Transform.Translate = cameraPostion;
    glm::vec3 direction = glm::normalize(cameraTarget - cameraPostion);

    float yaw = std::atan2(direction.x, -direction.z);
    camera->Transform.Rotation.y = yaw;

    float pitch = glm::asin(-direction.y);
    camera->Transform.Rotation.x = pitch;
}

glm::vec3 CameraSystem::GetForward(Ref<Camera>& camera)
{
    return glm::rotate(glm::inverse(camera->Transform.GetOrientation()), glm::vec3(0.0, 0.0, -1.0));
}
glm::vec3 CameraSystem::GetRight(Ref<Camera>& camera)
{
    return glm::rotate(glm::inverse(camera->Transform.GetOrientation()), glm::vec3(1.0, 0.0, 0.0));
}

glm::vec3 CameraSystem::GetUp(Ref<Camera>& camera)
{
    return glm::vec3(0.0, 1.0, 0.0);
}

}
