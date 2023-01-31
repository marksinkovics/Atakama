#ifndef CAMERA_SYSTEM_HPP
#define CAMERA_SYSTEM_HPP

namespace OGLSample
{

enum class Movement;
class Camera;

class CameraSystem
{
public:
    virtual void Update(Ref<Camera>& camera, float ts);
    virtual void Move(Ref<Camera>& camera, Movement movement, float ts);
    virtual void Rotate(Ref<Camera>& camera, glm::vec2 delta, float ts, bool constrainPitch = true);
    virtual void LookAt(Ref<Camera>& camera, const glm::vec3& cameraPostion, const glm::vec3& cameraTarget);
protected:
    virtual glm::vec3 GetForward(Ref<Camera>& camera);
    virtual glm::vec3 GetRight(Ref<Camera>& camera);
    virtual glm::vec3 GetUp(Ref<Camera>& camera);
private:
    float m_Speed = 3.0f;
    float m_MouseSpeed = 0.001f;
};

}

#endif
