#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

namespace OGLSample
{

class Mesh;
class SubMesh;


// from: https://stackoverflow.com/a/57595105
template <typename T, typename... Rest>
void hashCombine(std::size_t& seed, const T& v, const Rest&... rest)
{
    seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    (hashCombine(seed, rest), ...);
};

class AssetManager
{
public:
    static Ref<Mesh> LoadCube();
    static Ref<Mesh> LoadCube(glm::vec3 color);
    static Ref<Mesh> LoadTriangle();
    static Ref<Mesh> LoadAxis();
    static Ref<Mesh> LoadLightModel();
    static Ref<Mesh> LoadOBJFile(const std::filesystem::path& path);
};

}


#endif