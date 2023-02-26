#include "AssetManager.hpp"

#include <unordered_map>

namespace Atakama
{

void AssetManager::SetSelectedMeshId(int id)
{
    m_SelectedId = id;
}

int AssetManager::GetSelectedMeshId() const
{
    return m_SelectedId;
}

Ref<AssetManager> AssetManager::Get()
{
    return g_RuntimeGlobalContext.m_AssetManager;
}

void AssetManager::LoadTriangle(std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices)
{
    std::vector<Vertex> rawVertices {
        {{-0.5f, -0.5f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 1.f}, { 1.0f, 0.0f, 0.0f}},
        {{ 0.5f, -0.5f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 1.f}, { 0.0f, 1.0f, 0.0f}},
        {{ 0.0f,  0.5f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 1.f}, { 0.0f, 0.0f, 1.0f}},
    };

    AssetManager::GenerateIndices(rawVertices, vertices, indices);
}

void AssetManager::LoadAxis(std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices)
{
    std::vector<Vertex> rawVertices {
        {{0.0f, 0.0f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {1.0f, 0.0f, 0.0f}},
        {{3.0f, 0.0f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {1.0f, 0.0f, 0.0f}},
        {{0.0f, 0.0f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {0.0f, 1.0f, 0.0f}},
        {{0.0f, 3.0f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {0.0f, 1.0f, 0.0f}},
        {{0.0f, 0.0f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {0.0f, 0.0f, 1.0f}},
        {{0.0f, 0.0f, 3.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {0.0f, 0.0f, 1.0f}},
    };
    

    AssetManager::GenerateIndices(rawVertices, vertices, indices);
}

//Ref<Mesh> AssetManager::LoadLightModel()
//{
//    std::vector<Vertex> rawVertices {
//        {{-1.0f, -1.0f, 0.0f}, {0.f, 0.f}, {0.0f, 0.0f, 1.0f} },
//        {{ 1.0f,  1.0f, 0.0f}, {0.f, 0.f}, {0.0f, 0.0f, 1.0f} },
//        {{-1.0f,  1.0f, 0.0f}, {0.f, 0.f}, {0.0f, 0.0f, 1.0f} },
//        {{ 1.0f,  1.0f, 0.0f}, {0.f, 0.f}, {0.0f, 0.0f, 1.0f} },
//        {{-1.0f, -1.0f, 0.0f}, {0.f, 0.f}, {0.0f, 0.0f, 1.0f} },
//        {{ 1.0f, -1.0f, 0.0f}, {0.f, 0.f}, {0.0f, 0.0f, 1.0f} }
//    };
//
//    std::vector<Vertex> vertices;
//    std::vector<uint32_t> indices;
//    AssetManager::GenerateIndices(rawVertices, vertices, indices);
//
//    auto subMesh = CreateScope<SubMesh>(vertices, indices);
//    auto mesh = CreateRef<Mesh>();
//    mesh->AddSubMesh(std::move(subMesh));
//    RegisterMesh(mesh);
//    return mesh;
//}

void AssetManager::LoadOBJFile(const std::filesystem::path& path, std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices)
{
    std::vector<uint32_t> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    LOG_DEBUG("Loading OBJ from path: {}", path);

    FILE* file = fopen(path.c_str(), "r");
    if(!file)
    {
        std::cerr << "Path " << path << " could not be opened.\n";
        return;
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
                return;
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
    
    std::unordered_map<Vertex, uint32_t> uniqueVertices{};
    
    for( unsigned int i=0; i<vertexIndices.size(); i++ )
    {
        Vertex vertex{};
        
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
}

Ref<Mesh> AssetManager::LoadMesh(const std::filesystem::path& path)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    LoadOBJFile(path, vertices, indices);

    return CreateRef<Mesh>(vertices, indices);
}

void AssetManager::GenerateIndices(const std::vector<Vertex>& input, std::vector<Vertex>& output, std::vector<uint32_t>& indices)
{
    std::unordered_map<Vertex, uint32_t> uniqueVertices {};
    
    for (const Vertex& vertex : input)
    {
        if (uniqueVertices.count(vertex) == 0)
        {
            uniqueVertices[vertex] = static_cast<uint32_t>(output.size());
            output.push_back(vertex);
        }
        
        indices.push_back(uniqueVertices[vertex]);
    }
}

void AssetManager::LoadQuad(std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices)
{
    std::vector<Vertex> rawVertices {
        {{-1.0f,  1.0f, 0.0f}, {0.0f, 1.0f}, {0.f, 0.f, 1.f}, { 1.0f, 0.0f, 1.0f}},
        {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {0.f, 0.f, 1.f}, { 1.0f, 0.0f, 1.0f}},
        {{ 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, {0.f, 0.f, 1.f}, { 1.0f, 0.0f, 1.0f}},

        {{-1.0f,  1.0f, 0.0f}, {0.0f, 1.0f}, {0.f, 0.f, 1.f}, { 0.0f, 1.0f, 1.0f}},
        {{ 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, {0.f, 0.f, 1.f}, { 0.0f, 1.0f, 1.0f}},
        {{ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f}, {0.f, 0.f, 1.f}, { 0.0f, 1.0f, 1.0f}}
    };

    AssetManager::GenerateIndices(rawVertices, vertices, indices);
}

void AssetManager::LoadSkyBox(std::vector<Vertex>& vertices,  std::vector<uint32_t>& indices)
{
    std::vector<Vertex> rawVertices {
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},

        {{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},

        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},

        {{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},

        {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},

        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}
    };

    AssetManager::GenerateIndices(rawVertices, vertices, indices);
}

}
