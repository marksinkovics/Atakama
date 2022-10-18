#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <glm/glm.hpp>

namespace OGLSample
{

class Mesh;
class SubMesh;

class AssetManager
{
public:
    static Ref<Mesh> LoadCube();
    static Ref<Mesh> LoadCube(glm::vec3 color);
    static Ref<Mesh> LoadTriangle();
    static Ref<Mesh> LoadOBJFile(const std::filesystem::path& path);
    static Ref<Mesh> LoadAxis();
    static Ref<Mesh> LoadLightModel();
};

}


#endif