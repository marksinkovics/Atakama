#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include "Mesh.hpp"
#include "SubMesh.hpp"

namespace OGLSample
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
    void UpdateSelected(int id);
private:
    std::vector<Ref<Mesh>> m_AllocatedMeshes;
    int m_SelectedId {0};
};

}


#endif
