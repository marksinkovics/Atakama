#include "Entity.hpp"
#include "Components/Components.hpp"

namespace Atakama
{

Entity::Entity(entt::entity handle, Scene* scene)
: m_Handle(handle), m_Scene(scene)
{

}

void Entity::SetParent(entt::entity parent)
{
    AddOrReplace<Parent>(parent);
}

void Entity::AddChildren(std::set<entt::entity> children)
{
    AddOrReplace<Children>(children);

    for (entt::entity childId : children)
    {
        Entity child { childId, m_Scene };
        child.SetParent(m_Handle);
    }
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
