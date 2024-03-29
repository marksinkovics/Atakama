#include "TransformComponent.hpp"

namespace Atakama
{

glm::quat TransformComponent::GetOrientation() const
{
    glm::quat pitch = glm::angleAxis(Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat yaw = glm::angleAxis(Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat roll = glm::angleAxis(Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    return glm::normalize(pitch * yaw * roll);
}

glm::mat4 TransformComponent::GetMat4()
{
    glm::mat4 translate = glm::translate(glm::mat4(1.0), Translate);
    glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));
    glm::mat4 scale = glm::scale(glm::mat4(1.0), Scale);
//    return translate * glm::mat4_cast(GetOrientation()) * scale;
    return translate * rotation * scale;
}

glm::mat3 TransformComponent::GetInverseMat3()
{
    return glm::inverseTranspose(glm::mat3(GetMat4()));;
}

glm::mat4 TransformComponent::GetInverseMat4()
{
    return glm::inverseTranspose(GetMat4());
}

}
