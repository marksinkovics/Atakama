#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/gtx/quaternion.hpp>

namespace OGLSample
{

class Transform
{
public:
    Transform() = default;
    Transform(const Transform&) = default;


    glm::quat GetOrientation() const;
        
    glm::mat4 GetMat4();
    glm::mat3 GetInverseMat3();
    glm::mat4 GetInverseMat4();    
public:
    glm::vec3 Translate { 0.0f, 0.0f, 0.0f };
    glm::vec3 Rotation { 0.0f, 0.0f, 0.0f }; // Pitch, Yaw, Roll
    glm::vec3 Scale { 1.0f, 1.0f, 1.0f };
};

}

#endif
