#ifndef MODEL_HPP
#define MODEL_HPP

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
  Model(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colors, std::vector<glm::vec2> uvs);
  ~Model();

  void Bind();
  void Unbind();

  void Draw();

  glm::mat4 GetModelMatrix();
  void SetModelMatrix(glm::mat4 modelMatrix);

private:
  std::vector<glm::vec3> m_Vertices;
  std::vector<glm::vec3> m_Colors;
  std::vector<glm::vec2> m_UVs;

  GLuint m_VAOId;

  GLuint m_VertexBufferId;
  GLuint m_ColorBufferId;
  GLuint m_UVBufferId;

  glm::mat4 m_ModelMatrix {1.0f};
};

Ref<Model> LoadCubeModel();
Ref<Model> LoadTriangle();
Ref<Model> LoadOBJFile(const std::filesystem::path& path);

}

#endif