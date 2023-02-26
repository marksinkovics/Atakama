#ifndef ATAKAMA_ASSET_MANAGER_HPP
#define ATAKAMA_ASSET_MANAGER_HPP

#include "Vertex.hpp"
#include "MeshObject.hpp"

namespace Atakama
{

class AssetManager
{
public:

    static Ref<AssetManager> Get();

    void LoadTriangle(std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices);
    void LoadAxis(std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices);
    void LoadOBJFile(const std::filesystem::path& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
    Ref<MeshObject> LoadMeshObject(const std::filesystem::path& path);

    void LoadQuad(std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices);
    void LoadSkyBox(std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices);
    void GenerateIndices(const std::vector<Vertex>& input, std::vector<Vertex>& output, std::vector<uint32_t>& indices);

    void SetSelectedMeshId(int id);
    int GetSelectedMeshId() const;
private:
    int m_SelectedId {0};
};

}


#endif
