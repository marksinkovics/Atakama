#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace OGLSample
{

class Model
{
public:
  Model(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colors);
  ~Model();

  void bind();
  void unbind();

  void draw();

  glm::mat4 getModelMatrix();
  void setModelMatrix(glm::mat4 modelMatrix);

private:
  std::vector<glm::vec3> m_Vertices;
  std::vector<glm::vec3> m_Colors;

  GLuint m_VAOId;

  GLuint m_VertexBufferId;
  GLuint m_ColorBufferId;

  glm::mat4 m_ModelMatrix {1.0f};
};

Model LoadCubeModel();
Model LoadTriangle();

}

#endif
