#include "AssetManager.hpp"

#include <unordered_map>

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

namespace OGLSample
{

Ref<Mesh> AssetManager::LoadTriangle()
{
    std::vector<SubMesh::Vertex> rawVertices {
        {{-0.5f, -0.5f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 1.f}, { 1.0f, 0.0f, 0.0f}},
        {{ 0.5f, -0.5f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 1.f}, { 0.0f, 1.0f, 0.0f}},
        {{ 0.0f,  0.5f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 1.f}, { 0.0f, 0.0f, 1.0f}},
    };
    
    std::vector<SubMesh::Vertex> vertices;
    std::vector<uint32_t> indices;
    
    AssetManager::GenerateIndices(rawVertices, vertices, indices);

    auto subMesh = CreateScope<SubMesh>(vertices, indices);
    auto mesh = CreateRef<Mesh>();
    mesh->AddSubMesh(std::move(subMesh));
    return mesh;
}

Ref<Mesh> AssetManager::LoadAxis()
{
    std::vector<SubMesh::Vertex> rawVertices {
        {{0.0f, 0.0f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {1.0f, 0.0f, 0.0f}},
        {{3.0f, 0.0f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {1.0f, 0.0f, 0.0f}},
        {{0.0f, 0.0f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {0.0f, 1.0f, 0.0f}},
        {{0.0f, 3.0f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {0.0f, 1.0f, 0.0f}},
        {{0.0f, 0.0f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {0.0f, 0.0f, 1.0f}},
        {{0.0f, 0.0f, 3.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {0.0f, 0.0f, 1.0f}},
    };
    
    std::vector<SubMesh::Vertex> vertices;
    std::vector<uint32_t> indices;
        
    AssetManager::GenerateIndices(rawVertices, vertices, indices);
    
    auto subMesh1 = CreateScope<SubMesh>(rawVertices);
    subMesh1->SetMode(DrawingMode::Lines);
    
    auto subMesh2 = CreateScope<SubMesh>(rawVertices);
    subMesh1->SetMode(DrawingMode::Lines);
    subMesh2->SetModelMatrix(glm::translate(glm::mat4(1.0f), {1.0f, 0.0f, 1.0f}));

    std::vector<Scope<SubMesh>> subMeshes;
    subMeshes.push_back(std::move(subMesh1));
    subMeshes.push_back(std::move(subMesh2));
    return CreateRef<Mesh>(subMeshes);
}

Ref<Mesh> AssetManager::LoadLightModel()
{
    std::vector<SubMesh::Vertex> rawVertices {
        {{-1.0f, -1.0f, 0.0f}, {0.f, 0.f}, {0.0f, 0.0f, 1.0f} },
        {{ 1.0f,  1.0f, 0.0f}, {0.f, 0.f}, {0.0f, 0.0f, 1.0f} },
        {{-1.0f,  1.0f, 0.0f}, {0.f, 0.f}, {0.0f, 0.0f, 1.0f} },
        {{ 1.0f,  1.0f, 0.0f}, {0.f, 0.f}, {0.0f, 0.0f, 1.0f} },
        {{-1.0f, -1.0f, 0.0f}, {0.f, 0.f}, {0.0f, 0.0f, 1.0f} },
        {{ 1.0f, -1.0f, 0.0f}, {0.f, 0.f}, {0.0f, 0.0f, 1.0f} }
    };
    
    std::vector<SubMesh::Vertex> vertices;
    std::vector<uint32_t> indices;
    AssetManager::GenerateIndices(rawVertices, vertices, indices);
    
    auto subMesh = CreateScope<SubMesh>(vertices, indices);
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

void AssetManager::GenerateIndices(const std::vector<SubMesh::Vertex>& input, std::vector<SubMesh::Vertex>& output, std::vector<uint32_t>& indices)
{
    std::unordered_map<SubMesh::Vertex, uint32_t> uniqueVertices {};
    
    for (const SubMesh::Vertex& vertex : input)
    {
        if (uniqueVertices.count(vertex) == 0)
        {
            uniqueVertices[vertex] = static_cast<uint32_t>(output.size());
            output.push_back(vertex);
        }
        
        indices.push_back(uniqueVertices[vertex]);
    }
}

}
