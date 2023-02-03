#include "Scene.hpp"

#include "FileSystem.hpp"
#include "AssetManager.hpp"

namespace Atakama
{

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

Ref<PointLight> Scene::GetLight() const
{
    return m_PointLight;
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

void SandboxScene::LoadLight()
{
    m_PointLight = CreateRef<PointLight>(glm::vec4(4.f, 4.f, 4.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f));
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
