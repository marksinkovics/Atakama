#ifndef ATAKAMA_ASSET_MANAGER_HPP
#define ATAKAMA_ASSET_MANAGER_HPP

#include "Vertex.hpp"
#include "Mesh.hpp"
#include "SubMesh.hpp"
#include "MeshObject.hpp"

namespace Atakama
{

class AssetManager
{
public:

    static Ref<AssetManager> Get();

    Ref<Mesh> LoadTriangle();
    void LoadAxis(std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices);
    Ref<Mesh> LoadAxis();

    Ref<Mesh> LoadLightModel();
    void LoadOBJFile(const std::filesystem::path& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
    Ref<Mesh> LoadMesh(const std::filesystem::path& path);
    Ref<MeshObject> LoadMeshObject(const std::filesystem::path& path);

    void LoadQuad(std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices);
    Ref<Mesh> LoadQuad();
    void LoadSkyBox(std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices);
    Ref<Mesh> LoadSkyBox();
    void GenerateIndices(const std::vector<Vertex>& input, std::vector<Vertex>& output, std::vector<uint32_t>& indices);

    int RegisterMesh(Ref<Mesh>& mesh);
    void SetSelectedMeshId(int id);
    int GetSelectedMeshId() const;
private:
    std::vector<Ref<Mesh>> m_AllocatedMeshes;
    int m_SelectedId {0};
};

}


#endif
