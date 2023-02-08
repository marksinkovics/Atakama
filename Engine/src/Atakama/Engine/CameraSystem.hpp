#ifndef ATAKAMA_CAMERA_SYSTEM_HPP
#define ATAKAMA_CAMERA_SYSTEM_HPP

namespace Atakama
{

enum class Movement;
class Entity;

class CameraSystem
{
public:
    virtual void Update(Entity cameraEntity, float ts);
    virtual void Move(Entity cameraEntity, Movement movement, float ts);
    virtual void Rotate(Entity cameraEntity, glm::vec2 delta, float ts, bool constrainPitch = true);
    virtual void LookAt(Entity cameraEntity, const glm::vec3& cameraPostion, const glm::vec3& cameraTarget);
protected:
    virtual glm::vec3 GetForward(Entity cameraEntity);
    virtual glm::vec3 GetRight(Entity cameraEntity);
    virtual glm::vec3 GetUp(Entity cameraEntity);
private:
    float m_Speed = 3.0f;
    float m_MouseSpeed = 0.001f;
};

}

#endif
