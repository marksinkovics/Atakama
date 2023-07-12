#ifndef ATAKAMA_ASSET_MANAGER_HPP
#define ATAKAMA_ASSET_MANAGER_HPP

#include "Atakama/Engine/Vertex.hpp"
#include "Atakama/Engine/Mesh.hpp"
#include "Atakama/Engine/Texture.hpp"

namespace Atakama
{

class OBJImporter;
class AssetLibrary;

class AssetManager
{
public:
    AssetManager();

    static Ref<AssetManager> Get();

    void Preload();

    Ref<Mesh> LoadMesh(const std::filesystem::path& path);

    Ref<Texture> GetTextureById(const std::string& id) const;
    Ref<Mesh> GetMeshById(const std::string& id) const;
    std::vector<Ref<Mesh>> GetModelById(const std::string& id) const;

    void ImportModel(std::filesystem::path& path);

private:
    std::map<std::string, Ref<Texture>> m_Textures;
    std::map<std::string, Ref<Mesh>> m_Meshes;
    std::map<std::string, std::vector<Ref<Mesh>>> m_Models;
    int m_SelectedId {0};

    Ref<OBJImporter> m_OBJImporter;
    Ref<AssetLibrary> m_AssetLibrary;


    
};

}


#endif
