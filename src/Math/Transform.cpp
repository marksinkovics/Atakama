#include "Transform.hpp"

namespace OGLSample
{

Transform::Transform() {};

void Transform::SetTranslate(const glm::vec3& translate)
{
    m_Translate = translate;
}

glm::vec3 Transform::GetTranslate()
{
    return m_Translate;
}

void Transform::Scale(const glm::vec3& scale)
{
    m_Scale += scale;
}

glm::vec3 Transform::GetScale()
{
    return m_Scale;
}

void Transform::Orientation(const glm::quat& orientation)
{
    m_Orientation = orientation;
    glm::vec3 angles = glm::eulerAngles(m_Orientation);
    m_Pitch = angles.x;
    m_Yaw = angles.y;
    m_Roll = angles.z;
}

glm::quat Transform::GetOrientation() const
{
    return m_Orientation;
}

float Transform::GetYaw()
{
    return m_Yaw;
}

float Transform::GetRoll()
{
    return m_Roll;
}

float Transform::GetPitch()
{
    return m_Pitch;
}

void Transform::SetYaw(float angle)
{
    m_Yaw = angle;
    UpdateOrientation();
}

void Transform::SetRoll(float angle)
{
    m_Roll = angle;
    UpdateOrientation();
}

void Transform::SetPitch(float angle)
{
    m_Pitch = angle;
    UpdateOrientation();
}

void Transform::UpdateOrientation()
{
    glm::quat pitch = glm::angleAxis(m_Pitch, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat yaw = glm::angleAxis(m_Yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat roll = glm::angleAxis(m_Roll, glm::vec3(0.0f, 0.0f, 1.0f));
    m_Orientation = glm::normalize(pitch * yaw * roll);
}

glm::mat4 Transform::GetMat4()
{
    glm::mat4 translate = glm::translate(glm::mat4(1.0), (m_Translate * glm::vec3(-1)));
    glm::mat4 scale = glm::scale(glm::mat4(1.0), m_Scale);
    return scale * glm::mat4_cast(m_Orientation) * translate;
}

glm::vec3 Transform::GetForward() const
{
    return glm::conjugate(m_Orientation) * glm::vec3(0.0f, 0.0f, -1.0f);
}

glm::vec3 Transform::GetLeft() const
{
    return glm::conjugate(m_Orientation) * glm::vec3(-1.0, 0.0f, 0.0f);
}

glm::vec3 Transform::GetUp() const
{
    return glm::conjugate(m_Orientation) * glm::vec3(0.0f, 1.0f, 0.0f);
}

void Transform::MoveForward(float movement)
{
    m_Translate += GetForward() * movement;
}

void Transform::MoveBackward(float movement)
{
    m_Translate -= GetForward() * movement;
}

void Transform::MoveLeft(float movement)
{
    m_Translate += GetLeft() * movement;
}

void Transform::MoveRight(float movement)
{
    m_Translate -= GetLeft() * movement;
}

void Transform::MoveUp(float movement)
{
    m_Translate += GetUp() * movement;
}

void Transform::MoveDown(float movement)
{
    m_Translate -= GetUp() * movement;
}

void Transform::Move(Movement movement, float value)
{
    if (movement == Movement::Forward)
    {
        MoveForward(value);
    }
    if (movement == Movement::Backward)
    {
        MoveBackward(value);
    }
    if (movement == Movement::Right)
    {
        MoveRight(value);
    }
    if (movement == Movement::Left)
    {
        MoveLeft(value);
    }
    if (movement == Movement::Up)
    {
        MoveUp(value);
    }
    if (movement == Movement::Down)
    {
        MoveDown(value);
    }
}

}
