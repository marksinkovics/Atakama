#include "PointLight.hpp"
#include "Mesh.hpp"
#include "AssetManager.hpp"

namespace OGLSample
{

PointLight::PointLight(const glm::vec4& position, const glm::vec4& color)
: m_Position(position), m_Color(color)
{

    m_Mesh = AssetManager::LoadCube(glm::vec3(m_Color));
    m_Mesh->SetModelMatrix(glm::scale(m_Mesh->GetModelMatrix(), {0.2f, 0.2f, 0.2f}));
    m_Mesh->SetModelMatrix(glm::translate(m_Mesh->GetModelMatrix(), glm::vec3(m_Position)));
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
