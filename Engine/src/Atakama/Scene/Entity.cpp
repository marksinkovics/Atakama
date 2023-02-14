#include "Entity.hpp"
#include "Components/Components.hpp"

namespace Atakama
{

Entity::Entity(entt::entity handle, Scene* scene)
: m_Handle(handle), m_Scene(scene)
{

}

void Entity::SetParent(const Entity& parent)
{
    AddOrReplace<Parent>(parent.m_Handle);
}

Entity Entity::GetParent() const
{
    if (HasComponent<Parent>())
        return {GetComponent<Parent>().Parent, m_Scene};
    return {};
}

void Entity::AddChildren(std::set<Entity> children)
{
    std::set<entt::entity> result;
    for (const Entity& child : children)
    {
        result.insert(child.m_Handle);
    }

    for (const Entity& child : GetChildren())
    {
        result.insert(child.m_Handle);
    }

    AddOrReplace<Children>(result);

    for (Entity child : children)
    {
        child.SetParent(*this);
    }
}

std::set<Entity> Entity::GetChildren() const
{
    if (HasComponent<Children>())
    {
        std::set<Entity> result;
        for (const entt::entity& childId : GetComponent<Children>().Children)
        {
            result.insert({childId, m_Scene});
        }
        return result;
    }
    return {};
}

std::set<Entity> Entity::GetDescendents() const
{
    std::set<Entity> result { {m_Handle, m_Scene} };
    for (const auto& childId : GetChildren())
    {
        Entity child { childId, this->m_Scene };
        std::set<Entity> fetched = child.GetDescendents();
        result.insert(fetched.begin(), fetched.end());
    }

    return result;
}

bool Entity::operator==(const Entity& other) const
{
    return m_Handle == other.m_Handle && m_Scene == other.m_Scene;
}

bool Entity::operator!=(const Entity& other) const
{
    return !(*this == other);
}

bool Entity::operator<(const Entity &other) const
{
    return m_Handle < other.m_Handle;
}

}
