#include "AssetManager.hpp"

#include "Atakama/Core/FileSystem.hpp"
#include "Atakama/Asset/AssimpImporter.hpp"
#include "Atakama/Asset/OBJImporter.hpp"
#include "Atakama/Asset/AssetLibrary.hpp"

#include <sstream>

namespace Atakama
{

AssetManager::AssetManager()
{
    m_OBJImporter = CreateRef<OBJImporter>();
    m_AssetLibrary = CreateRef<AssetLibrary>();
}


void AssetManager::Preload()
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

    m_Meshes["cube"] = LoadMesh(FileSystem::GetModelPath() / "cube.obj");
    m_Meshes["vikingRoom"] = LoadMesh(FileSystem::GetModelPath() / "viking_room.obj");
    m_Meshes["quad"] = LoadMesh(FileSystem::GetModelPath() / "quad.obj");
    m_Meshes["canvas"] = m_AssetLibrary->LoadQuad();
    m_Meshes["axis"] = m_AssetLibrary->LoadAxis();
    m_Meshes["skybox"] = m_AssetLibrary->LoadSkyBox();
    m_Meshes["triangle"] = m_AssetLibrary->LoadTriangle();
    m_Meshes["grid"] = m_AssetLibrary->LoadGrid();

}

Ref<AssetManager> AssetManager::Get()
{
    return g_RuntimeGlobalContext.m_AssetManager;
}

Ref<Texture> AssetManager::GetTextureById(const std::string& id) const
{
    auto it = m_Textures.find(id);
    if (it == m_Textures.end())
    {
        LOG_ERROR("Cannot find texture by id {}", id)
        return nullptr;
    }
    return it->second;

}

Ref<Mesh> AssetManager::GetMeshById(const std::string& id) const
{
    auto it = m_Meshes.find(id);
    if (it == m_Meshes.end())
    {
        LOG_ERROR("Cannot find mesh by id {}", id)
        return nullptr;
    }
    return it->second;
}

std::vector<Ref<Mesh>> AssetManager::GetModelById(const std::string& id) const
{
    auto it = m_Models.find(id);
    if (it == m_Models.end())
    {
        LOG_ERROR("Cannot find model by id {}", id)
            return {};
    }
    return it->second;

}

Ref<Mesh> AssetManager::LoadMesh(const std::filesystem::path& path)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    bool result = m_OBJImporter->Import(path, vertices, indices);
    if (!result) {
        LOG_ERROR("OBJ (on path: {}) failed to load", path);
    }
    return CreateRef<Mesh>(vertices, indices);
}


void AssetManager::ImportModel(std::filesystem::path& path)
{
    AssimpImporter importer(path);
    if (importer.Import())
    {
        m_Models[path.filename().string()] = importer.GetMeshes();
        m_Textures.insert(importer.GetTextures().begin(), importer.GetTextures().end());
    }
}


}
