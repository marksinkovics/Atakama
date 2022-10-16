#ifndef MODEL_UTILS_HPP
#define MODEL_UTILS_HPP

#include "Model.hpp"

#include <glm/glm.hpp>

namespace OGLSample
{

Ref<Model> LoadCubeModel();
Ref<Model> LoadCubeModel(glm::vec3 color);
Ref<Model> LoadTriangle();
Ref<Model> LoadOBJFile(const std::filesystem::path& path);
Ref<Model> LoadAxis();
Ref<Model> LoadLightModel();

}

#endif