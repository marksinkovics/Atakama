#include "SubMesh.hpp"

namespace OGLSample
{

bool SubMesh::Vertex::operator==(const Vertex &other) const
{
    return
        position == other.position &&
        color == other.color &&
        normal == other.normal &&
        uv == other.uv;
}

SubMesh::SubMesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
    : m_Positions({}), m_Indices(indices), m_UVs({}), m_Normals({}), m_Colors({})
{
    const size_t vertexCount = vertices.size();

    m_Positions.reserve(vertexCount);
    m_Colors.reserve(vertexCount);
    m_UVs.reserve(vertexCount);
    m_Normals.reserve(vertexCount);

    for (const auto& vertex : vertices) {
        m_Positions.push_back(vertex.position);
        m_Colors.push_back(vertex.color);
        m_UVs.push_back(vertex.uv);
        m_Normals.push_back(vertex.normal);
    }

    GenerateVertexArray();
}

SubMesh::SubMesh(std::vector<glm::vec3> positions, std::vector<uint32_t> indices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<glm::vec3> colors)
  : m_Positions(positions), m_Indices(indices), m_UVs(uvs), m_Normals(normals), m_Colors(colors)
{
    if (m_Colors.size() == 0) {
        m_Colors.resize(m_Positions.size(), {1.0f, 1.0f, 1.0f});
    }

    GenerateVertexArray();
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

void SubMesh::GenerateVertexArray()
{
    // VAO
	glGenVertexArrays(1, &m_VAOId);
	glBindVertexArray(m_VAOId);

    // Position
    glGenBuffers(1, &m_VertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_Positions.size(), m_Positions.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    if (m_Indices.size() > 0)
    {
        // Index
        glGenBuffers(1, &m_IndexBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(uint32_t), m_Indices.data(), GL_STATIC_DRAW);
    }

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

    // Colors
    glGenBuffers(1, &m_ColorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_Colors.size(), m_Colors.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);
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

    if (m_Indices.size() > 0)
    {
        glDrawElements(m_Type, m_Indices.size(), GL_UNSIGNED_INT, (void*)0);
    }
    else
    {
        glDrawArrays(m_Type, 0, m_Positions.size());
    }

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
