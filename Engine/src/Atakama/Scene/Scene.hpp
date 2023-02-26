#ifndef ATAKAMA_SCENE_HPP
#define ATAKAMA_SCENE_HPP

#include "Atakama/Engine/Shader.hpp"
#include "Atakama/Engine/Texture.hpp"

#include <map>
#include <entt/entt.hpp>

namespace Atakama
{

class Entity;
class RenderSystem;
class Shader;

class Scene
{
public:
    Scene();
    virtual ~Scene() = default;

    Entity CreateEntity(const std::string& name = "");
    void RemoveEntity(Entity entity);

    Entity GetPrimaryCameraEntity();

    virtual void Init();
    virtual void LoadLight();
    virtual void LoadSkyBox();
    virtual void LoadTextures();
    virtual void LoadMeshes();
    
    Entity GetLight();
    Entity GetSkyBox();

    Ref<Texture> GetTextureById(const std::string& id) const;

    const entt::registry& GetRegistry() const { return m_Registry; }
protected:
    std::map<std::string, Ref<Texture>> m_Textures;

    entt::registry m_Registry;
    friend class Entity;
};

class SandboxScene: public Scene
{
public:
    SandboxScene();
    virtual ~SandboxScene() = default;
    virtual void LoadLight() override;
    virtual void LoadSkyBox() override;
    virtual void LoadTextures() override;
    virtual void LoadMeshes() override;
};

}


#endif
