#include "AssetManager.hpp"

#include "Mesh.hpp"
#include "SubMesh.hpp"

#include <unordered_map>

namespace std
{
    template<>
    struct hash<OGLSample::SubMesh::Vertex>
    {
        size_t operator()(const OGLSample::SubMesh::Vertex &vertex) const
        {
            size_t seed = 0;
            OGLSample::hashCombine(seed, vertex.position, vertex.color, vertex.normal, vertex.uv);
            return seed;
        }
    };
}

namespace OGLSample
{

Ref<Mesh> AssetManager::LoadCube()
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

    std::vector<uint32_t> indices {};

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

    auto subMesh = CreateScope<SubMesh>(vertices, indices, uvs, normals, colors);
    auto mesh = CreateRef<Mesh>();
    mesh->AddSubMesh(std::move(subMesh));
    return mesh;
}

Ref<Mesh> AssetManager::LoadCube(glm::vec3 color)
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

    std::vector<uint32_t> indices {};
    std::vector<glm::vec3> colors(vertices.size(), color);

    std::vector<glm::vec2> uvs  {};
    std::vector<glm::vec3> normals {};

    auto subMesh = CreateScope<SubMesh>(vertices, indices, uvs, normals, colors);
    auto mesh = CreateRef<Mesh>();
    mesh->AddSubMesh(std::move(subMesh));
    return mesh;
}

Ref<Mesh> AssetManager::LoadTriangle()
{
    std::vector<glm::vec3> vertices {
        {-0.5f, -0.5f, 0.0f},
        { 0.5f, -0.5f, 0.0f},
        { 0.0f,  0.5f, 0.0f},
    };

    std::vector<uint32_t> indices {};

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

    auto subMesh = CreateScope<SubMesh>(vertices, indices, uvs, normals, colors);
    auto mesh = CreateRef<Mesh>();
    mesh->AddSubMesh(std::move(subMesh));
    return mesh;
}

Ref<Mesh> AssetManager::LoadAxis()
{
    std::vector<glm::vec3> vertices {
        {0.0f, 0.0f, 0.0f},
        {3.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 3.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 3.0f},
    };

    std::vector<uint32_t> indices {};

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

    auto subMesh1 = CreateScope<SubMesh>(vertices, indices, uvs, normals, colors);
    subMesh1->SetType(GL_LINES);

    auto subMesh2 = CreateScope<SubMesh>(vertices, indices, uvs, normals, colors);
    subMesh2->SetType(GL_LINES);
    subMesh2->SetModelMatrix(glm::translate(glm::mat4(1.0f), {1.0f, 0.0f, 1.0f}));

    std::vector<Scope<SubMesh>> subMeshes;
    subMeshes.push_back(std::move(subMesh1));
    subMeshes.push_back(std::move(subMesh2));
    return CreateRef<Mesh>(subMeshes);
}

Ref<Mesh> AssetManager::LoadLightModel()
{
    std::vector<glm::vec3> vertices {
        {-1.0f, -1.0f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {-1.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {-1.0f, -1.0f, 0.0f},
        {1.0f, -1.0f, 0.0f}
    };

    std::vector<uint32_t> indices {};
    std::vector<glm::vec3> colors;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals {
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
    };

    auto subMesh = CreateScope<SubMesh>(vertices, indices, uvs, normals, colors);
    auto mesh = CreateRef<Mesh>();
    mesh->AddSubMesh(std::move(subMesh));
    return mesh;
}

Ref<Mesh> AssetManager::LoadOBJFile(const std::filesystem::path& path)
{
    std::vector<uint32_t> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    std::vector<SubMesh::Vertex> vertices{};
    std::vector<uint32_t> indices {};

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
			temp_positions.push_back(vertex);
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

    std::unordered_map<SubMesh::Vertex, uint32_t> uniqueVertices{};

    for( unsigned int i=0; i<vertexIndices.size(); i++ )
    {
        SubMesh::Vertex vertex{};

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		vertex.position = temp_positions[vertexIndex-1];
		vertex.uv = {temp_uvs[uvIndex-1].x, 1.f - temp_uvs[uvIndex-1].y};
		vertex.normal =  temp_normals[normalIndex-1];

        if (uniqueVertices.count(vertex) == 0)
        {
            uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
            vertices.push_back(vertex);
        }

        indices.push_back(uniqueVertices[vertex]);
	}

    fclose(file);

    auto subMesh = CreateScope<SubMesh>(vertices, indices);
    auto mesh = CreateRef<Mesh>();
    mesh->AddSubMesh(std::move(subMesh));
    return mesh;
}

}
