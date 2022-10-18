#include "SubMesh.hpp"

#include <glm/gtc/matrix_inverse.hpp>

namespace OGLSample
{

SubMesh::SubMesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<glm::vec3> colors)
  : m_Vertices(vertices), m_UVs(uvs), m_Normals(normals), m_Colors(colors)
{
    // VAO
	glGenVertexArrays(1, &m_VAOId);
	glBindVertexArray(m_VAOId);

    // Position
    glGenBuffers(1, &m_VertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_Vertices.size(), m_Vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // UV
    glGenBuffers(1, &m_UVBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_UVBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_UVs.size(), m_UVs.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Normal
    glGenBuffers(1, &m_NormalBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_NormalBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_Normals.size(), m_Normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    if (m_Colors.size() == 0) {
        m_Colors.resize(m_Vertices.size(), {1.0f, 1.0f, 1.0f});
    }

    // Colors
    glGenBuffers(1, &m_ColorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_Colors.size(), m_Colors.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);
}

SubMesh::~SubMesh()
{
    // glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &m_VertexBufferId);
    glDeleteBuffers(1, &m_NormalBufferId);
    glDeleteBuffers(1, &m_UVBufferId);
    glDeleteBuffers(1, &m_ColorBufferId);

    glDeleteVertexArrays(1, &m_VAOId);
}

void SubMesh::Bind()
{
    glBindVertexArray(m_VAOId);
}

void SubMesh::Unbind()
{
    glBindVertexArray(0);
}

void SubMesh::Draw()
{
    Bind();
    glDrawArrays(m_Type, 0, m_Vertices.size());
    Unbind();
}

glm::mat4 SubMesh::GetModelMatrix()
{
    return m_ModelMatrix;
}

void SubMesh::SetModelMatrix(glm::mat4 modelMatrix)
{
    m_ModelMatrix = modelMatrix;
}

glm::mat3 SubMesh::GetNormalMatrix()
{
    return glm::inverseTranspose(glm::mat3(m_ModelMatrix));
}

void SubMesh::SetTexture(Ref<Texture> texture)
{
    m_Texture = texture;
}

Ref<Texture> SubMesh::GetTexture()
{
    return m_Texture;
}

GLuint SubMesh::GetType()
{
    return m_Type;
}

void SubMesh::SetType(GLuint type)
{
    m_Type = type;
}

}
