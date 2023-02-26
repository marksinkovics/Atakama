#include "Scene.hpp"

#include "Atakama/Core/FileSystem.hpp"
#include "Atakama/Engine/AssetManager.hpp"
#include "Atakama/Engine/RenderSystem.hpp"
#include "Atakama/Engine/Shader.hpp"
#include "Atakama/Engine/Mesh.hpp"

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

void Scene::RemoveEntity(Entity entity)
{
    std::string& name = entity.GetComponent<NameComponent>().Name;
    LOG_INFO("Remove entity (id: {}, name: {})", (uint32_t)entity.m_Handle, name);

    if (entity.HasComponent<Children>())
    {
        Children& children = entity.GetComponent<Children>();
        for (auto& childId : children.Children)
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
    LoadLight();
    LoadTextures();
    LoadMeshes();
    LoadSkyBox();
}

void Scene::LoadLight()
{
    
}

void Scene::LoadSkyBox()
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

Entity Scene::GetSkyBox()
{
    auto view = m_Registry.view<SkyBoxComponent>();
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
    auto& meshComponent = pointLightEntity.AddComponent<MeshComponent>();
    meshComponent.Mesh = AssetManager::Get()->LoadMesh(FileSystem::GetModelPath() / "cube.obj");
}

void SandboxScene::LoadSkyBox()
{
    Entity skyBoxEntity = CreateEntity("Skybox");
    skyBoxEntity.AddComponent<SkyBoxComponent>();
    skyBoxEntity.AddComponent<TransformComponent>();
    skyBoxEntity.AddComponent<TextureComponent>(m_Textures["skybox"]);

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    AssetManager::Get()->LoadSkyBox(vertices, indices);
    Ref<Mesh> mesh = CreateRef<Mesh>(vertices, indices);
    skyBoxEntity.AddComponent<MeshComponent>(mesh);
}

void SandboxScene::LoadTextures()
{
    m_Textures["uvtemplate"] = Texture2D::Create(FileSystem::GetTexturePath() / "uvtemplate.bmp");
    m_Textures["uvmap"] = Texture2D::Create(FileSystem::GetTexturePath() / "uvmap.png");
    m_Textures["vikingRoom"] = Texture2D::Create(FileSystem::GetTexturePath() / "viking_room.png");
    m_Textures["skybox"] = TextureCube::Create({
        FileSystem::GetTexturePath() / "right.jpg",
        FileSystem::GetTexturePath() / "left.jpg",
        FileSystem::GetTexturePath() / "top.jpg",
        FileSystem::GetTexturePath() / "bottom.jpg",
        FileSystem::GetTexturePath() / "front.jpg",
        FileSystem::GetTexturePath() / "back.jpg"
    });

}

void SandboxScene::LoadMeshes()
{

    {
        Entity meshEntity = CreateEntity("UVTemplate Mesh");
        Ref<Mesh> Mesh = AssetManager::Get()->LoadMesh(FileSystem::GetModelPath() / "cube.obj");
        meshEntity.AddComponent<MeshComponent>(Mesh);
        meshEntity.AddComponent<TextureComponent>(m_Textures["uvtemplate"]);
        TransformComponent& transform = meshEntity.AddComponent<TransformComponent>();
        transform.Translate = {-1.8f, 1.0f, -1.f};
    }

    {
        Entity meshEntity = CreateEntity("UVMap Mesh");
        Ref<Mesh> Mesh = AssetManager::Get()->LoadMesh(FileSystem::GetModelPath() / "cube.obj");
        meshEntity.AddComponent<MeshComponent>(Mesh);
        meshEntity.AddComponent<TextureComponent>(m_Textures["uvmap"]);
        TransformComponent& transform = meshEntity.AddComponent<TransformComponent>();
        transform.Translate = {1.8f, 1.0f, -1.f};
    }

    {
        Entity meshEntity = CreateEntity("Viking room");
        Ref<Mesh> Mesh = AssetManager::Get()->LoadMesh(FileSystem::GetModelPath() / "viking_room.obj");
        meshEntity.AddComponent<MeshComponent>(Mesh);
        meshEntity.AddComponent<TextureComponent>(m_Textures["vikingRoom"]);
        TransformComponent& transform = meshEntity.AddComponent<TransformComponent>();
        transform.Scale = {1.5f, 1.5f, 1.5f};
        transform.Translate = {-1.8f, 0.1f, 1.8f};
        transform.Rotation = {glm::radians(-90.0f), 0.0f, 0.f};
    }

    {
        Entity meshEntity = CreateEntity("Floor");
        Ref<Mesh> Mesh = AssetManager::Get()->LoadMesh(FileSystem::GetModelPath() / "quad.obj");
        meshEntity.AddComponent<MeshComponent>(Mesh);
        TransformComponent& transform = meshEntity.AddComponent<TransformComponent>();
        transform.Scale = {3.f, 1.f, 3.f};
    }

    {

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        AssetManager::Get()->LoadAxis(vertices, indices);

        Ref<Mesh> parent = CreateRef<Mesh>(vertices, indices);
        parent->SetMode(DrawingMode::Lines);
        Ref<Mesh> child = CreateRef<Mesh>(vertices, indices);
        child->SetMode(DrawingMode::Lines);

        Entity parentEntity = CreateEntity("Axis Parent");
        parentEntity.AddComponent<DebugComponent>();
        parentEntity.AddComponent<MeshComponent>(parent);
        TransformComponent& parentTransform = parentEntity.AddComponent<TransformComponent>();

        Entity childEntity = CreateEntity("Axis Child");
        childEntity.AddComponent<DebugComponent>();
        childEntity.AddComponent<MeshComponent>(child);
        TransformComponent& childTransform = childEntity.AddComponent<TransformComponent>();
        childTransform.Translate = {1.0f, 0.0f, 1.0f};

        parentEntity.AddChildren({childEntity});

    }
}

}
