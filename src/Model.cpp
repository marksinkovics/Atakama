#include "Model.hpp"

#include <iostream>

namespace OGLSample
{

Model::Model(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colors, std::vector<glm::vec2> uvs)
  : m_Vertices(vertices), m_Colors(colors), m_UVs(uvs)
{
	glGenVertexArrays(1, &m_VAOId);
	glBindVertexArray(m_VAOId);

    glGenBuffers(1, &m_VertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_Vertices.size(), m_Vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    if (m_Colors.size() > 0) {
        glGenBuffers(1, &m_ColorBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, m_ColorBufferId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_Colors.size(), m_Colors.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, m_ColorBufferId);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    }

    if (m_UVs.size() > 0) {
        glGenBuffers(1, &m_UVBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, m_UVBufferId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_UVs.size(), m_UVs.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, m_UVBufferId);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    }

    glBindVertexArray(0);
}

Model::~Model()
{
    // glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &m_VertexBufferId);
    glDeleteBuffers(1, &m_ColorBufferId);
    glDeleteBuffers(1, &m_UVBufferId);

    glDeleteVertexArrays(1, &m_VAOId);
}

void Model::bind()
{
    glBindVertexArray(m_VAOId);
}
void Model::unbind()
{
    glBindVertexArray(0);
}

void Model::draw()
{
    bind();
    glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
    unbind();
}

glm::mat4 Model::getModelMatrix()
{
    return m_ModelMatrix;
}

void Model::setModelMatrix(glm::mat4 modelMatrix)
{
    m_ModelMatrix = modelMatrix;
}

Model LoadCubeModel()
{
    std::vector<glm::vec3> vertices {
        {-1.0f,-1.0f,-1.0f},
        {-1.0f,-1.0f, 1.0f},
        {-1.0f, 1.0f, 1.0f},
        { 1.0f, 1.0f,-1.0f},
        {-1.0f,-1.0f,-1.0f},
        {-1.0f, 1.0f,-1.0f},
        { 1.0f,-1.0f, 1.0f},
        {-1.0f,-1.0f,-1.0f},
        { 1.0f,-1.0f,-1.0f},
        { 1.0f, 1.0f,-1.0f},
        { 1.0f,-1.0f,-1.0f},
        {-1.0f,-1.0f,-1.0f},
        {-1.0f,-1.0f,-1.0f},
        {-1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f,-1.0f},
        { 1.0f,-1.0f, 1.0f},
        {-1.0f,-1.0f, 1.0f},
        {-1.0f,-1.0f,-1.0f},
        {-1.0f, 1.0f, 1.0f},
        {-1.0f,-1.0f, 1.0f},
        { 1.0f,-1.0f, 1.0f},
        { 1.0f, 1.0f, 1.0f},
        { 1.0f,-1.0f,-1.0f},
        { 1.0f, 1.0f,-1.0f},
        { 1.0f,-1.0f,-1.0f},
        { 1.0f, 1.0f, 1.0f},
        { 1.0f,-1.0f, 1.0f},
        { 1.0f, 1.0f, 1.0f},
        { 1.0f, 1.0f,-1.0f},
        {-1.0f, 1.0f,-1.0f},
        { 1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f,-1.0f},
        {-1.0f, 1.0f, 1.0f},
        { 1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f, 1.0f},
        { 1.0f,-1.0f, 1.0f}
    };

    std::vector<glm::vec3> colors {
        {0.583f,  0.771f,  0.014f},
        {0.609f,  0.115f,  0.436f},
        {0.327f,  0.483f,  0.844f},
        {0.822f,  0.569f,  0.201f},
        {0.435f,  0.602f,  0.223f},
        {0.310f,  0.747f,  0.185f},
        {0.597f,  0.770f,  0.761f},
        {0.559f,  0.436f,  0.730f},
        {0.359f,  0.583f,  0.152f},
        {0.483f,  0.596f,  0.789f},
        {0.559f,  0.861f,  0.639f},
        {0.195f,  0.548f,  0.859f},
        {0.014f,  0.184f,  0.576f},
        {0.771f,  0.328f,  0.970f},
        {0.406f,  0.615f,  0.116f},
        {0.676f,  0.977f,  0.133f},
        {0.971f,  0.572f,  0.833f},
        {0.140f,  0.616f,  0.489f},
        {0.997f,  0.513f,  0.064f},
        {0.945f,  0.719f,  0.592f},
        {0.543f,  0.021f,  0.978f},
        {0.279f,  0.317f,  0.505f},
        {0.167f,  0.620f,  0.077f},
        {0.347f,  0.857f,  0.137f},
        {0.055f,  0.953f,  0.042f},
        {0.714f,  0.505f,  0.345f},
        {0.783f,  0.290f,  0.734f},
        {0.722f,  0.645f,  0.174f},
        {0.302f,  0.455f,  0.848f},
        {0.225f,  0.587f,  0.040f},
        {0.517f,  0.713f,  0.338f},
        {0.053f,  0.959f,  0.120f},
        {0.393f,  0.621f,  0.362f},
        {0.673f,  0.211f,  0.457f},
        {0.820f,  0.883f,  0.371f},
        {0.982f,  0.099f,  0.879f}
    };

    std::vector<glm::vec2> uvs  {
        {0.000059f, 1.0f-0.000004f},
        {0.000103f, 1.0f-0.336048f},
        {0.335973f, 1.0f-0.335903f},
        {1.000023f, 1.0f-0.000013f},
        {0.667979f, 1.0f-0.335851f},
        {0.999958f, 1.0f-0.336064f},
        {0.667979f, 1.0f-0.335851f},
        {0.336024f, 1.0f-0.671877f},
        {0.667969f, 1.0f-0.671889f},
        {1.000023f, 1.0f-0.000013f},
        {0.668104f, 1.0f-0.000013f},
        {0.667979f, 1.0f-0.335851f},
        {0.000059f, 1.0f-0.000004f},
        {0.335973f, 1.0f-0.335903f},
        {0.336098f, 1.0f-0.000071f},
        {0.667979f, 1.0f-0.335851f},
        {0.335973f, 1.0f-0.335903f},
        {0.336024f, 1.0f-0.671877f},
        {1.000004f, 1.0f-0.671847f},
        {0.999958f, 1.0f-0.336064f},
        {0.667979f, 1.0f-0.335851f},
        {0.668104f, 1.0f-0.000013f},
        {0.335973f, 1.0f-0.335903f},
        {0.667979f, 1.0f-0.335851f},
        {0.335973f, 1.0f-0.335903f},
        {0.668104f, 1.0f-0.000013f},
        {0.336098f, 1.0f-0.000071f},
        {0.000103f, 1.0f-0.336048f},
        {0.000004f, 1.0f-0.671870f},
        {0.336024f, 1.0f-0.671877f},
        {0.000103f, 1.0f-0.336048f},
        {0.336024f, 1.0f-0.671877f},
        {0.335973f, 1.0f-0.335903f},
        {0.667969f, 1.0f-0.671889f},
        {1.000004f, 1.0f-0.671847f},
        {0.667979f, 1.0f-0.335851f}
    };

    return Model(vertices, {}, uvs);
}

Model LoadTriangle()
{
    std::vector<glm::vec3> vertices {
        {-1.0f, -1.0f, 0.0f},
        { 1.0f, -1.0f, 0.0f},
        { 0.0f,  1.0f, 0.0f},
    };

    std::vector<glm::vec3> colors {
        { 1.0f, 0.0f, 0.0f},
        { 0.0f, 1.0f, 0.0f},
        { 0.0f, 0.0f, 1.0f},
    };

    return Model(vertices, colors, {});
}

}
