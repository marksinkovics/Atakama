#ifndef ATAKAMA_ENGINE_ENTITY_HPP
#define ATAKAMA_ENGINE_ENTITY_HPP

#include "Scene.hpp"

#include <entt/entt.hpp>

namespace Atakama
{

class Entity
{
public:
    Entity() = default;
    Entity(entt::entity handle, Scene* scene);
    Entity(const Entity& other) = default;
    ~Entity() = default;

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        T& component = m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
        return component;
    }

    template<typename T>
    void RemoveComponent()
    {
        m_Scene->m_Registry.remove<T>(m_Handle);
    }

    template<typename T>
    T& GetComponent()
    {
        return m_Scene->m_Registry.get<T>(m_Handle);
    }

    template<typename T>
    bool HasComponent()
    {
        return m_Scene->m_Registry.try_get<T>(m_Handle) != nullptr;
    }

    operator bool() const { return m_Handle != entt::null; }
    operator entt::entity() const { return m_Handle; }
    operator uint32_t() const { return (uint32_t)m_Handle; }

    bool operator==(const Entity& other) const;
    bool operator!=(const Entity& other) const;
private:
    entt::entity m_Handle { entt::null };
    Scene* m_Scene { nullptr };

    friend class Scene;
};

}

#endif
