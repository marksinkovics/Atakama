#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Engine/InputSystem.hpp"
#include <glm/gtx/quaternion.hpp>

namespace OGLSample
{

class Transform
{
public:
    Transform();
    
    void SetTranslate(const glm::vec3& translate);

    glm::vec3 GetTranslate();

    void Scale(const glm::vec3& scale);
    glm::vec3 GetScale();
    
    void Orientation(const glm::quat& orientation);

    glm::quat GetOrientation() const;

    float GetYaw();
    float GetRoll();
    float GetPitch();

    void SetYaw(float angle);
    void SetRoll(float angle);
    void SetPitch(float angle);

    void UpdateOrientation();
        
    glm::mat4 GetMat4();
    
    glm::vec3 GetForward() const;
    glm::vec3 GetLeft() const;
    glm::vec3 GetUp() const;
        
    void MoveForward(float movement);
    void MoveBackward(float movement);
    void MoveLeft(float movement);
    void MoveRight(float movement);
    void MoveUp(float movement);
    void MoveDown(float movement);
    void Move(Movement movement, float value);
private:
    glm::vec3 m_Translate { 0.0f, 0.0f, 0.0f };
    glm::quat m_Orientation { 1.0f, 0.0f, 0.0f, 0.0f };
    float m_Yaw   { 0.0f };
    float m_Pitch { 0.0f };
    float m_Roll  { 0.0f };
    glm::vec3 m_Scale { 1.0f, 1.0f, 1.0f };
};

}

#endif
