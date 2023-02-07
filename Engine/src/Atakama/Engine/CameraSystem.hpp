#ifndef ATAKAMA_CAMERA_SYSTEM_HPP
#define ATAKAMA_CAMERA_SYSTEM_HPP

namespace Atakama
{

enum class Movement;
class Camera;

class CameraSystem
{
public:
    virtual void Update(Camera& camera, float ts);
    virtual void Move(Camera& camera, Movement movement, float ts);
    virtual void Rotate(Camera& camera, glm::vec2 delta, float ts, bool constrainPitch = true);
    virtual void LookAt(Camera& camera, const glm::vec3& cameraPostion, const glm::vec3& cameraTarget);
protected:
    virtual glm::vec3 GetForward(Camera& camera);
    virtual glm::vec3 GetRight(Camera& camera);
    virtual glm::vec3 GetUp(Camera& camera);
private:
    float m_Speed = 3.0f;
    float m_MouseSpeed = 0.001f;
};

}

#endif
