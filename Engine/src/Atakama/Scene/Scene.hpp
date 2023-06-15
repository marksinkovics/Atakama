#ifndef ATAKAMA_SCENE_HPP
#define ATAKAMA_SCENE_HPP

#include "Atakama/Engine/Shader.hpp"
#include "Atakama/Engine/Texture.hpp"

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
    virtual void LoadMeshes();

    Entity GetLight();
    Entity GetSkyBox();

    const entt::registry& GetRegistry() const { return m_Registry; }

    Entity GetSelectedEntity();
    void SetSelectedEntity(Entity entity);
    bool HasSelectedEntity() const;

    void AddModeById(const std::string& modelId);
protected:
    entt::registry m_Registry;
    entt::entity m_SelectedEntity { entt::null };
    friend class Entity;
};

class SandboxScene: public Scene
{
public:
    SandboxScene();
    virtual ~SandboxScene() = default;
    virtual void LoadLight() override;
    virtual void LoadSkyBox() override;
    virtual void LoadMeshes() override;
};

}


#endif
