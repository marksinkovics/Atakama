#include "Scene.hpp"

#include "Atakama/Core/FileSystem.hpp"
#include "Atakama/Engine/AssetManager.hpp"
#include "Atakama/Engine/RenderSystem.hpp"
#include "Atakama/Engine/Shader.hpp"
#include "Atakama/Engine/Mesh.hpp"
#include "Atakama/Engine/CameraSystem.hpp"

#include "Atakama/Scene/Entity.hpp"

#include "Components/Components.hpp"
#include "Components/TransformComponent.hpp"

namespace Atakama
{

Scene::Scene()
{
}

Entity Scene::CreateEntity(const std::string& name)
{
    Entity entity(m_Registry.create(), this);
    entity.AddComponent<NameComponent>(name);
    return entity;
}

void Scene::RemoveEntity(Entity entity)
{
    std::string& name = entity.GetComponent<NameComponent>().Name;
    LOG_INFO("Remove entity (id: {}, name: {})", (uint32_t)entity.m_Handle, name);

    if (entity.HasComponent<Children>())
    {
        Children& children = entity.GetComponent<Children>();
        for (auto& childId : children.Values)
        {
            Entity child { childId, this };
            RemoveEntity(child);
        }
        entity.RemoveComponent<Children>();
    }

    m_Registry.destroy(entity.m_Handle);

}

Entity Scene::GetPrimaryCameraEntity()
{
    auto view = m_Registry.view<CameraComponent>();
    for (auto entity : view)
    {
        const auto& cameraComponent = view.get<CameraComponent>(entity);
        if (cameraComponent.Primary)
        {
            return Entity(entity, this);
        }
    }
    return Entity();
}

void Scene::Init()
{
    LoadCamera();
    LoadLight();
    LoadMeshes();
    LoadSkyBox();
}

void Scene::LoadCamera()
{
    Entity cameraEntity = CreateEntity("Camera #1");
    CameraComponent& cameraComponent = cameraEntity.AddComponent<CameraComponent>(Camera::Mode::Perspective);
    TransformComponent& transformComponent = cameraEntity.AddComponent<TransformComponent>();
    g_RuntimeGlobalContext.m_CameraSystem->LookAt(cameraEntity, { 5.0f, 5.f, 5.f }, { 0.0f, 0.0f, 0.0f });
    cameraComponent.Primary = true;
}

void Scene::LoadLight()
{
    
}

void Scene::LoadSkyBox()
{

}

void Scene::LoadMeshes()
{
    
}

Entity Scene::GetLight()
{
    auto view = m_Registry.view<PointLightComponent>();
    for (auto entity : view)
    {
        return Entity(entity, this);
    }
    return Entity();
}

Entity Scene::GetSkyBox()
{
    auto view = m_Registry.view<SkyBoxComponent>();
    for (auto entity : view)
    {
        return Entity(entity, this);
    }
    return Entity();
}

Entity Scene::GetSelectedEntity()
{
    return Entity(m_SelectedEntity, this);
}

void Scene::SetSelectedEntity(Entity entity)
{
    m_SelectedEntity = entity;
}

bool Scene::HasSelectedEntity() const
{
    return m_SelectedEntity != entt::null;
}

void Scene::AddModeById(const std::string& modelId)
{
    Entity rootEntity = CreateEntity(modelId);
    TransformComponent& transform = rootEntity.AddComponent<TransformComponent>();
    rootEntity.AddComponent<DebugComponent>();

    std::vector<Ref<Mesh>> meshes = AssetManager::Get()->GetModelById(modelId);
    for (int i = 0; i < meshes.size(); i++) {
        const std::string name = fmt::format("Mesh {}", i);
        Entity meshEntity = CreateEntity(name);
        meshEntity.AddComponent<MeshComponent>(meshes[i]);
        if (meshes[i]->HasTextureId()) 
        {
            meshEntity.AddComponent<TextureComponent>(AssetManager::Get()->GetTextureById(meshes[i]->GetTextureId()));
        }
        TransformComponent& transform = meshEntity.AddComponent<TransformComponent>();
        rootEntity.AddChildren({ meshEntity });
    }
}

//
// Sandbox scene
//

SandboxScene::SandboxScene()
{
}

void SandboxScene::LoadLight()
{
    Entity pointLightEntity = CreateEntity("Point Light #1");
    pointLightEntity.AddComponent<DebugComponent>();
    TransformComponent& transformComponent = pointLightEntity.AddComponent<TransformComponent>();
    transformComponent.Translate = glm::vec3(4.f, 4.f, 4.f);
    transformComponent.Scale = glm::vec3(0.2f, 0.2f, 0.2f);
    PointLightComponent& pointLightComponent = pointLightEntity.AddComponent<PointLightComponent>();
    pointLightComponent.Color = glm::vec4(1.f, 1.f, 1.f, 1.f);
    pointLightEntity.AddComponent<MeshComponent>(AssetManager::Get()->GetMeshById("cube"));
}

void SandboxScene::LoadSkyBox()
{
    Entity skyBoxEntity = CreateEntity("Skybox");
    skyBoxEntity.AddComponent<SkyBoxComponent>();
    skyBoxEntity.AddComponent<TransformComponent>();
    skyBoxEntity.AddComponent<TextureComponent>(AssetManager::Get()->GetTextureById("skybox"));
    skyBoxEntity.AddComponent<MeshComponent>(AssetManager::Get()->GetMeshById("skybox"));
}

void SandboxScene::LoadMeshes()
{
    {
        Entity meshEntity = CreateEntity("UVTemplate Mesh");
        meshEntity.AddComponent<MeshComponent>(AssetManager::Get()->GetMeshById("cube"));
        meshEntity.AddComponent<TextureComponent>(AssetManager::Get()->GetTextureById("uvtemplate"));
        TransformComponent& transform = meshEntity.AddComponent<TransformComponent>();
        transform.Translate = {-1.8f, 1.0f, -1.f};
    }

    {
        Entity meshEntity = CreateEntity("UVMap Mesh");
        meshEntity.AddComponent<MeshComponent>(AssetManager::Get()->GetMeshById("cube"));
        meshEntity.AddComponent<TextureComponent>(AssetManager::Get()->GetTextureById("uvmap"));
        TransformComponent& transform = meshEntity.AddComponent<TransformComponent>();
        transform.Translate = {1.8f, 1.0f, -1.f};
    }

    {
        Entity meshEntity = CreateEntity("Viking room");
        meshEntity.AddComponent<MeshComponent>(AssetManager::Get()->GetMeshById("vikingRoom"));
        meshEntity.AddComponent<TextureComponent>(AssetManager::Get()->GetTextureById("vikingRoom"));
        TransformComponent& transform = meshEntity.AddComponent<TransformComponent>();
        transform.Scale = {1.5f, 1.5f, 1.5f};
        transform.Translate = {-1.8f, 0.1f, 1.8f};
        transform.Rotation = {glm::radians(-90.0f), 0.0f, 0.f};
    }

    {
        Entity meshEntity = CreateEntity("Floor");
        meshEntity.AddComponent<MeshComponent>(AssetManager::Get()->GetMeshById("quad"));
        TransformComponent& transform = meshEntity.AddComponent<TransformComponent>();
        transform.Scale = {3.f, 1.f, 3.f};
    }

    {
        Entity parentEntity = CreateEntity("Axis Parent");
        parentEntity.AddComponent<DebugComponent>();
        parentEntity.AddComponent<MeshComponent>(AssetManager::Get()->GetMeshById("axis"));
        TransformComponent& parentTransform = parentEntity.AddComponent<TransformComponent>();

        Entity childEntity = CreateEntity("Axis Child");
        childEntity.AddComponent<DebugComponent>();
        childEntity.AddComponent<MeshComponent>(AssetManager::Get()->GetMeshById("axis"));
        TransformComponent& childTransform = childEntity.AddComponent<TransformComponent>();
        childTransform.Translate = {1.0f, 0.0f, 1.0f};

        parentEntity.AddChildren({childEntity});
    }
}

}
