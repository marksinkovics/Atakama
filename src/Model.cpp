#include "Model.hpp"

#include <iostream>
#include <glm/gtc/matrix_inverse.hpp>

namespace OGLSample
{

Model::Model(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<glm::vec3> colors)
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

Model::~Model()
{
    // glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &m_VertexBufferId);
    glDeleteBuffers(1, &m_NormalBufferId);
    glDeleteBuffers(1, &m_UVBufferId);
    glDeleteBuffers(1, &m_ColorBufferId);

    glDeleteVertexArrays(1, &m_VAOId);
}

void Model::Bind()
{
    glBindVertexArray(m_VAOId);
}

void Model::Unbind()
{
    glBindVertexArray(0);
}

void Model::Draw()
{
    Bind();
    glDrawArrays(m_Type, 0, m_Vertices.size());
    Unbind();
}

glm::mat4 Model::GetModelMatrix()
{
    return m_ModelMatrix;
}

void Model::SetModelMatrix(glm::mat4 modelMatrix)
{
    m_ModelMatrix = modelMatrix;
}

glm::mat3 Model::GetNormalMatrix()
{
    return glm::inverseTranspose(glm::mat3(m_ModelMatrix));
}

void Model::SetTexture(Ref<Texture> texture)
{
    m_Texture = texture;
}

Ref<Texture> Model::GetTexture()
{
    return m_Texture;
}

GLuint Model::GetType()
{
    return m_Type;
}

void Model::SetType(GLuint type)
{
    m_Type = type;
}

Ref<Model> LoadCubeModel()
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

    std::vector<glm::vec3> normals {};

    return CreateRef<Model>(vertices, uvs, normals, colors);
}

Ref<Model> LoadCubeModel(glm::vec3 color)
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

    std::vector<glm::vec3> colors(vertices.size(), color);

    std::vector<glm::vec2> uvs  {};
    std::vector<glm::vec3> normals {};

    return CreateRef<Model>(vertices, uvs, normals, colors);
}

Ref<Model> LoadTriangle()
{
    std::vector<glm::vec3> vertices {
        {-0.5f, -0.5f, 0.0f},
        { 0.5f, -0.5f, 0.0f},
        { 0.0f,  0.5f, 0.0f},
    };

    std::vector<glm::vec3> colors {
        { 1.0f, 0.0f, 0.0f},
        { 0.0f, 1.0f, 0.0f},
        { 0.0f, 0.0f, 1.0f},
    };

    std::vector<glm::vec2> uvs {};
    std::vector<glm::vec3> normals {
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
    };

    return CreateRef<Model>(vertices, uvs, normals, colors);
}

Ref<Model> LoadOBJFile(const std::filesystem::path& path)
{
    std::vector<uint32_t> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;


    std::cout << "Loading OBJ model from path: " << path << "\n";
    FILE* file = fopen(path.c_str(), "r");
    if(!file)
    {
        std::cerr << "Path " << path << " could not be opened.\n";
        return nullptr;
    }

    while(1)
    {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF) {
            break; // end of file
        }

        if (strcmp(lineHeader, "v" ) == 0)
        {
            glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt" ) == 0)
        {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			temp_uvs.push_back(uv);
		}
        else if (strcmp( lineHeader, "vn" ) == 0){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
        }
        else if ( strcmp( lineHeader, "f" ) == 0 )
        {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9){
				printf("File can't be read by our simple parser\n");
				fclose(file);
				return nullptr;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
        }
        else
        {
			// Probably a comment, eat up the rest of the line
			char buffer[1000];
			fgets(buffer, 1000, file);
		}
    }

    for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex-1];
		glm::vec2 uv = temp_uvs[uvIndex-1];
		glm::vec3 normal = temp_normals[normalIndex-1];

		// Put the attributes in buffers
		vertices.push_back(vertex);
		uvs.push_back({uv.x, 1.f - uv.y});
		normals .push_back(normal);
	}

    fclose(file);

	return CreateRef<Model>(vertices, uvs, normals, colors);
}

Ref<Model> LoadAxis()
{
    std::vector<glm::vec3> vertices {
        {0.0f, 0.0f, 0.0f},
        {3.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 3.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 3.0f},
    };
    
    std::vector<glm::vec3> colors {
        {1.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
    };
    
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    
    auto model = CreateRef<Model>(vertices, uvs, normals, colors);
    model->SetType(GL_LINES);
    return model;
}

}
