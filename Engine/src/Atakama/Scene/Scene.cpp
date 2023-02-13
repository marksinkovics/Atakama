#include "Scene.hpp"

#include "Atakama/Core/FileSystem.hpp"
#include "Atakama/Engine/AssetManager.hpp"

#include "Atakama/Scene/Entity.hpp"

#include "Components/Components.hpp"
#include "Components/TransformComponent.hpp"

namespace Atakama
{

Scene::Scene()
{
    Entity cameraEntity = CreateEntity("Camera #1");
    CameraComponent& cameraComponent = cameraEntity.AddComponent<CameraComponent>(Camera::Mode::Perspective);
    TransformComponent& transformComponent = cameraEntity.AddComponent<TransformComponent>();
    cameraComponent.Primary = true;

    Entity parent = CreateEntity("Parent");
    Entity child1 = CreateEntity("Child #1");
    Entity child2 = CreateEntity("Child #2");
    Entity child3 = CreateEntity("Child #3");
    Entity child4 = CreateEntity("Child #4");
    parent.AddChildren({ child1, child2, child3, child4 });

    Entity child5 = CreateEntity("Child #4 - Grand Child #1");
    child4.AddChildren({ child5 });
}

Entity Scene::CreateEntity(const std::string& name)
{
    Entity entity(m_Registry.create(), this);
    entity.AddComponent<NameComponent>(name);
    return entity;
}

void Scene::DestroyEntity(Entity entity)
{
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
    LoadLight();
    LoadTextures();
    LoadMeshes();
}

void Scene::LoadLight()
{
    
}

void Scene::LoadTextures()
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


Ref<Texture> Scene::GetTextureById(const std::string& id) const
{
    auto it = m_Textures.find(id);
    if (it == m_Textures.end())
    {
        LOG_ERROR("Cannot find texture by id {}", id)
        return nullptr;
    }
    return it->second;
}

std::vector<Ref<Mesh>> Scene::GetMeshes() const
{
    return m_Meshes;
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
    TransformComponent& transformComponent = pointLightEntity.AddComponent<TransformComponent>();
    transformComponent.Translate = glm::vec3(4.f, 4.f, 4.f);
    transformComponent.Scale = glm::vec3(0.2f, 0.2f, 0.2f);
    PointLightComponent& pointLightComponent = pointLightEntity.AddComponent<PointLightComponent>();
    pointLightComponent.Color = glm::vec4(1.f, 1.f, 1.f, 1.f);
    MeshComponent& meshComponent = pointLightEntity.AddComponent<MeshComponent>();
    meshComponent.Mesh = AssetManager::Get()->LoadOBJFile(FileSystem::GetModelPath() / "cube.obj");
}

void SandboxScene::LoadTextures()
{
    m_Textures["uvtemplate"] = Texture2D::Create(FileSystem::GetTexturePath() / "uvtemplate.bmp");
    m_Textures["uvmap"] = Texture2D::Create(FileSystem::GetTexturePath() / "uvmap.png");
    m_Textures["vikingRoom"] = Texture2D::Create(FileSystem::GetTexturePath() / "viking_room.png");
}

void SandboxScene::LoadMeshes()
{
    {
        auto mesh = AssetManager::Get()->LoadOBJFile(FileSystem::GetModelPath() / "cube.obj");
        mesh->GetTransform()->Translate = {-1.8f, 1.0f, -1.f};
        mesh->GetSubMeshes()[0]->SetTexture(m_Textures["uvtemplate"]);
        m_Meshes.push_back(mesh);
    }
    
    {
        auto mesh = AssetManager::Get()->LoadOBJFile(FileSystem::GetModelPath() / "cube.obj");
        mesh->GetTransform()->Translate = { 1.8f, 1.0f, -1.f};
        mesh->GetSubMeshes()[0]->SetTexture(m_Textures["uvmap"]);
        m_Meshes.push_back(mesh);
    }
    
    {
        auto mesh = AssetManager::Get()->LoadOBJFile(FileSystem::GetModelPath() / "viking_room.obj");
        mesh->GetSubMeshes()[0]->SetTexture(m_Textures["vikingRoom"]);
        mesh->GetTransform()->Scale = {1.5f, 1.5f, 1.5f};
        mesh->GetTransform()->Translate = {-1.8f, 0.1f, 1.8f};
        mesh->GetTransform()->Rotation = {glm::radians(-90.0f), 0.0f, 0.f};
        m_Meshes.push_back(mesh);
    }
    
    {
        auto mesh = AssetManager::Get()->LoadOBJFile(FileSystem::GetModelPath() / "quad.obj");
        mesh->GetTransform()->Scale = {3.f, 1.f, 3.f};
        m_Meshes.push_back(mesh);
    }
}

}
