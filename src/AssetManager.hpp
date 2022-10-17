#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <glm/glm.hpp>

namespace OGLSample
{

class Model;

class AssetManager
{
public:
    static Ref<Model> LoadCubeModel();
    static Ref<Model> LoadCubeModel(glm::vec3 color);
    static Ref<Model> LoadTriangle();
    static Ref<Model> LoadOBJFile(const std::filesystem::path& path);
    static Ref<Model> LoadAxis();
    static Ref<Model> LoadLightModel();
};

}


#endif