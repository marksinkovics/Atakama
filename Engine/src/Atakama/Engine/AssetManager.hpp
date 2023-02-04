#ifndef ATAKAMA_ASSET_MANAGER_HPP
#define ATAKAMA_ASSET_MANAGER_HPP

#include "Mesh.hpp"
#include "SubMesh.hpp"

namespace Atakama
{

class AssetManager
{
public:

    static Ref<AssetManager> Get();

    Ref<Mesh> LoadTriangle();
    Ref<Mesh> LoadAxis();
    Ref<Mesh> LoadLightModel();
    Ref<Mesh> LoadOBJFile(const std::filesystem::path& path);
    Ref<Mesh> LoadQuad();
    Ref<Mesh> LoadSkyBox();
    void GenerateIndices(const std::vector<SubMesh::Vertex>& input, std::vector<SubMesh::Vertex>& output, std::vector<uint32_t>& indices);

    int RegisterMesh(Ref<Mesh>& mesh);
    void SetSelectedMeshId(int id);
    int GetSelectedMeshId() const;
private:
    std::vector<Ref<Mesh>> m_AllocatedMeshes;
    int m_SelectedId {0};
};

}


#endif
