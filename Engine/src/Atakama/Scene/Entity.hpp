#ifndef ATAKAMA_ENGINE_ENTITY_HPP
#define ATAKAMA_ENGINE_ENTITY_HPP

#include "Scene.hpp"

#include <entt/entt.hpp>

namespace Atakama
{

struct Parent;

class Entity
{
public:
    Entity() = default;
    Entity(entt::entity handle, Scene* scene);
    Entity(const Entity& other) = default;
    ~Entity() = default;

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
    }

    template<typename T>
    void RemoveComponent()
    {
        m_Scene->m_Registry.remove<T>(m_Handle);
    }

    template<typename T>
    T& GetComponent() const
    {
        return m_Scene->m_Registry.get<T>(m_Handle);
    }

    template<typename Ret, typename... Args>
    entt::any& GetComponents() const
    {
        return m_Scene->m_Registry.get<Ret(Args...)>(m_Handle);
    }

    template<typename T, typename... Args>
    T& AddOrReplace(Args&&... args)
    {
        return m_Scene->m_Registry.emplace_or_replace<T>(m_Handle, std::forward<Args>(args)...);
    }

    template<typename T>
    T* TryGetComponent()
    {
        return m_Scene->m_Registry.try_get<T>(m_Handle);
    }

    template<typename T>
    bool HasComponent() const
    {
        return m_Scene->m_Registry.try_get<T>(m_Handle) != nullptr;
    }

    void SetParent(const Entity& parent);
    Entity GetParent() const;

    void AddChildren(std::set<Entity> children);
    std::set<Entity> GetChildren() const;

    std::set<Entity> GetDescendents() const;
    std::set<Entity> GetAncestors() const;

    template<typename T>
    std::vector<T> GetAncestorComponents() const
    {
        std::vector<T> result;
        if (HasComponent<Parent>())
        {
            std::vector<T> fetched = GetParent().GetAncestorComponents<T>();
            std::copy(fetched.begin(), fetched.end(), std::back_inserter(result));
        }

        if (HasComponent<T>())
        {
            result.push_back(GetComponent<T>());
        }

        return result;
    }

    operator bool() const { return m_Handle != entt::null; }
    operator entt::entity() const { return m_Handle; }
    operator uint32_t() const { return (uint32_t)m_Handle; }
    operator int32_t() const { return (int32_t)m_Handle; }

    bool operator==(const Entity& other) const;
    bool operator!=(const Entity& other) const;
    bool operator<(const Entity &other) const;

    bool IsValid() { return m_Handle != entt::null; }
private:
    entt::entity m_Handle { entt::null };
    Scene* m_Scene { nullptr };

    friend class Scene;
};

}

#endif
