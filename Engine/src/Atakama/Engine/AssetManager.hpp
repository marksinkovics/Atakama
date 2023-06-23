#ifndef ATAKAMA_ASSET_MANAGER_HPP
#define ATAKAMA_ASSET_MANAGER_HPP

#include "Vertex.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

namespace Atakama
{

class AssetManager
{
public:
    static Ref<AssetManager> Get();

    void Preload();

    void LoadTriangle(std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices);
    void LoadAxis(std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices);
    void LoadOBJFile(const std::filesystem::path& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
    void LoadQuad(std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices);
    void LoadSkyBox(std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices);

    Ref<Mesh> LoadTriangle();
    Ref<Mesh> LoadAxis();
    Ref<Mesh> LoadMesh(const std::filesystem::path& path);
    Ref<Mesh> LoadQuad();
    Ref<Mesh> LoadSkyBox();
    Ref<Mesh> LoadGrid();

    void GenerateIndices(const std::vector<Vertex>& input, std::vector<Vertex>& output, std::vector<uint32_t>& indices);

    void SetSelectedMeshId(int id);
    int GetSelectedMeshId() const;

    Ref<Texture> GetTextureById(const std::string& id) const;
    Ref<Mesh> GetMeshById(const std::string& id) const;
    std::vector<Ref<Mesh>> GetModelById(const std::string& id) const;

    void ImportModel(std::filesystem::path& path);

private:
    std::map<std::string, Ref<Texture>> m_Textures;
    std::map<std::string, Ref<Mesh>> m_Meshes;
    std::map<std::string, std::vector<Ref<Mesh>>> m_Models;
    int m_SelectedId {0};
};

}


#endif
