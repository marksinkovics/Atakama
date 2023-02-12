#ifndef ATAKAMA_SCENE_HPP
#define ATAKAMA_SCENE_HPP

#include "Atakama/Engine/Shader.hpp"
#include "Atakama/Engine/Texture.hpp"
#include "Atakama/Engine/Mesh.hpp"

#include <map>
#include <entt/entt.hpp>

namespace Atakama
{

class Entity;

class Scene
{
public:
    Scene();
    virtual ~Scene() = default;

    Entity CreateEntity(const std::string& name = "");
    void DestroyEntity(Entity entity);

    Entity GetPrimaryCameraEntity();

    virtual void Init();
    virtual void LoadLight();
    virtual void LoadTextures();
    virtual void LoadMeshes();
    
    Entity GetLight();

    Ref<Texture> GetTextureById(const std::string& id) const;
    
    std::vector<Ref<Mesh>> GetMeshes() const;
    std::vector<Ref<Mesh>>::iterator begin() { return m_Meshes.begin(); }
    std::vector<Ref<Mesh>>::iterator end() { return m_Meshes.end(); }
    std::vector<Ref<Mesh>>::const_iterator begin() const { return m_Meshes.begin(); }
    std::vector<Ref<Mesh>>::const_iterator end() const { return m_Meshes.end(); }

    const entt::registry& GetRegistry() const { return m_Registry; }

protected:
    std::map<std::string, Ref<Texture>> m_Textures;
    std::vector<Ref<Mesh>> m_Meshes;

    entt::registry m_Registry;
    friend class Entity;
};

class SandboxScene: public Scene
{
public:
    SandboxScene();
    virtual ~SandboxScene() = default;
    virtual void LoadLight() override;
    virtual void LoadTextures() override;
    virtual void LoadMeshes() override;
};

}


#endif
