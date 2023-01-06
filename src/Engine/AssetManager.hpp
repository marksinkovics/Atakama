#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include "Mesh.hpp"
#include "SubMesh.hpp"

namespace OGLSample
{

class AssetManager
{
public:
    static uint32_t GenerateId();

    static Ref<Mesh> LoadTriangle();
    static Ref<Mesh> LoadAxis();
    static Ref<Mesh> LoadLightModel();
    static Ref<Mesh> LoadOBJFile(const std::filesystem::path& path);
    static Ref<Mesh> LoadQuad();
    static Ref<Mesh> LoadSkyBox();
    
    static void GenerateIndices(const std::vector<SubMesh::Vertex>& input, std::vector<SubMesh::Vertex>& output, std::vector<uint32_t>& indices);
};

}


#endif
