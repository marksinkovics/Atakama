#include "Entity.hpp"

namespace Atakama
{

Entity::Entity(entt::entity handle, Scene* scene)
: m_Handle(handle), m_Scene(scene)
{

}

bool Entity::operator==(const Entity& other) const
{
    return m_Handle == other.m_Handle && m_Scene == other.m_Scene;
}

bool Entity::operator!=(const Entity& other) const
{
    return !(*this == other);
}

}
