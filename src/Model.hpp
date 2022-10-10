#ifndef MODEL_HPP
#define MODEL_HPP

#include "Texture.hpp"

#include <vector>
#include <filesystem>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace OGLSample
{

class Model
{
public:
  Model(
    std::vector<glm::vec3> vertices,
    std::vector<glm::vec2> uvs,
    std::vector<glm::vec3> normals,
    std::vector<glm::vec3> colors);

  ~Model();

  void Bind();
  void Unbind();

  void Draw();

  // model = T * S * R
  glm::mat4 GetModelMatrix();
  void SetModelMatrix(glm::mat4 modelMatrix);

  glm::mat3 GetNormalMatrix();

  void SetTexture(Ref<Texture> texture);
  Ref<Texture> GetTexture();

private:
  std::vector<glm::vec3> m_Vertices;
  std::vector<glm::vec2> m_UVs;
  std::vector<glm::vec3> m_Normals;
  std::vector<glm::vec3> m_Colors;

  Ref<Texture> m_Texture;

  GLuint m_VAOId;

  GLuint m_VertexBufferId;
  GLuint m_NormalBufferId;
  GLuint m_UVBufferId;
  GLuint m_ColorBufferId;

  glm::mat4 m_ModelMatrix {1.0f};
};

Ref<Model> LoadCubeModel();
Ref<Model> LoadCubeModel(glm::vec3 color);
Ref<Model> LoadTriangle();
Ref<Model> LoadOBJFile(const std::filesystem::path& path);

}

#endif
