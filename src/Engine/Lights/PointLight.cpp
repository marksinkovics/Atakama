#include "PointLight.hpp"
#include "Engine/Mesh.hpp"
#include "Engine/AssetManager.hpp"
#include "FileSystem.hpp"

namespace Atakama
{

PointLight::PointLight(const glm::vec4& position, const glm::vec4& color)
: m_Position(position), m_Color(color)
{

    m_Mesh = AssetManager::Get()->LoadOBJFile(FileSystem::GetModelPath() / "cube.obj");
    m_Mesh->GetTransform()->Scale = {0.2f, 0.2f, 0.2f};
    m_Mesh->GetTransform()->Translate = glm::vec3(m_Position);
}

glm::vec4& PointLight::GetPositionRef()
{
    return m_Position;
}

glm::vec4& PointLight::GetColorRef()
{
    return m_Color;
}

glm::vec4 PointLight::GetPosition() const
{
    return m_Position;
}

glm::vec4 PointLight::GetColor() const
{
    return m_Color;
}

Ref<Mesh> PointLight::GetMesh() const
{
    return m_Mesh;
}


}
