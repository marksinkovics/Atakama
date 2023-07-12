#ifndef ATAKAMA_ASSET_LIBRARY_HPP
#define ATAKAMA_ASSET_LIBRARY_HPP

#include <Atakama/Engine/Vertex.hpp>

namespace Atakama
{

class Mesh;

class AssetLibrary
{
public:
    Ref<Mesh> LoadTriangle();
    Ref<Mesh> LoadAxis();
    Ref<Mesh> LoadQuad();
    Ref<Mesh> LoadSkyBox();
    Ref<Mesh> LoadGrid();
protected:
    void GenerateIndices(std::vector<Vertex>& input, std::vector<Vertex>& output, std::vector<uint32_t>& indices);
};

}

#endif