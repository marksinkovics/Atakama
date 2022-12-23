#include "Scene.hpp"

#include "FileSystem.hpp"
#include "AssetManager.hpp"

namespace OGLSample
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
        return nullptr;
    return it->second;
}

Ref<Mesh> Scene::GetModelById(const std::string& id) const
{
    auto it = m_Meshes.find(id);
    if (it == m_Meshes.end())
        return nullptr;
    return it->second;
}

void SandboxScene::LoadLight()
{
    m_PointLight = CreateRef<PointLight>(glm::vec4(4.f, 4.f, 4.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f));
}

void SandboxScene::LoadTextures()
{
    m_Textures["uvtemplate"] = CreateRef<Texture>(FileSystem::GetTexturePath() / "uvtemplate.bmp");
    m_Textures["uvmap"] = CreateRef<Texture>(FileSystem::GetTexturePath() / "uvmap.png");
    m_Textures["vikingRoom"] = CreateRef<Texture>(FileSystem::GetTexturePath() / "viking_room.png");
    m_Textures["wall"] = CreateRef<Texture>(FileSystem::GetTexturePath() / "wall.jpg");
}

void SandboxScene::LoadMeshes()
{
    m_Meshes["axis"] = AssetManager::LoadAxis();
    m_Meshes["triangle"] = AssetManager::LoadTriangle();
    m_Meshes["smoothVase"] = AssetManager::LoadOBJFile(FileSystem::GetModelPath() / "smooth_vase.obj");

    {
        auto mesh = AssetManager::LoadOBJFile(FileSystem::GetModelPath() / "cube.obj");
        mesh->Translate({-1.8f, 1.0f, -1.f});
        mesh->GetSubMeshes()[0]->SetTexture(m_Textures["uvtemplate"]);
        m_Meshes["cube"] = mesh;
    }
    
    {
        auto mesh = AssetManager::LoadOBJFile(FileSystem::GetModelPath() / "cube.obj");
        mesh->Translate({ 1.8f, 1.0f, -1.f});
        mesh->GetSubMeshes()[0]->SetTexture(m_Textures["uvmap"]);
        m_Meshes["cube2"] = mesh;
    }
    
    {
        auto mesh = AssetManager::LoadOBJFile(FileSystem::GetModelPath() / "viking_room.obj");
        mesh->GetSubMeshes()[0]->SetTexture(m_Textures["vikingRoom"]);
        mesh->Scale({1.5f, 1.5f, 1.5f});
        mesh->Translate({-1.0f, 0.1f, 1.f});
        mesh->Rotate(glm::radians(90.0f), {-1.f, 0.f, 0.f});
        m_Meshes["vikingRoom"] = mesh;
    }
    
    {
        auto mesh = AssetManager::LoadOBJFile(FileSystem::GetModelPath() / "quad.obj");
        mesh->Rotate(glm::radians(180.0f), {0.f, 0.f, -1.f});
        mesh->Scale({3.f, 1.f, 3.f});
        mesh->Translate({0.f, 0.f, 0.f});
        m_Meshes["floor"] = mesh;
    }
}
 
}
