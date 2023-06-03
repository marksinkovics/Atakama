#include "AssetManager.hpp"

#include "Atakama/Core/FileSystem.hpp"

namespace Atakama
{

void AssetManager::Preload()
{
    m_Textures["uvtemplate"] = Texture2D::Create(FileSystem::GetTexturePath() / "uvtemplate.bmp");
    m_Textures["uvmap"] = Texture2D::Create(FileSystem::GetTexturePath() / "uvmap.png");
    m_Textures["vikingRoom"] = Texture2D::Create(FileSystem::GetTexturePath() / "viking_room.png");
    m_Textures["skybox"] = TextureCube::Create({
        FileSystem::GetTexturePath() / "right.jpg",
        FileSystem::GetTexturePath() / "left.jpg",
        FileSystem::GetTexturePath() / "top.jpg",
        FileSystem::GetTexturePath() / "bottom.jpg",
        FileSystem::GetTexturePath() / "front.jpg",
        FileSystem::GetTexturePath() / "back.jpg"
    });
    
    m_Meshes["cube"] = LoadMesh(FileSystem::GetModelPath() / "cube.obj");
    m_Meshes["vikingRoom"] = LoadMesh(FileSystem::GetModelPath() / "viking_room.obj");
    m_Meshes["quad"] = LoadMesh(FileSystem::GetModelPath() / "quad.obj");
    m_Meshes["canvas"] = LoadQuad();
    m_Meshes["axis"] = LoadAxis();
    m_Meshes["skybox"] = LoadSkyBox();
    m_Meshes["triangle"] = LoadTriangle();
}

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

Ref<Texture> AssetManager::GetTextureById(const std::string& id) const
{
    auto it = m_Textures.find(id);
    if (it == m_Textures.end())
    {
        LOG_ERROR("Cannot find texture by id {}", id)
        return nullptr;
    }
    return it->second;

}

Ref<Mesh> AssetManager::GetMeshById(const std::string& id) const
{
    auto it = m_Meshes.find(id);
    if (it == m_Meshes.end())
    {
        LOG_ERROR("Cannot find texture by id {}", id)
        return nullptr;
    }
    return it->second;

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

    //LOG_DEBUG("Loading OBJ from path: {}", path);

    std::ifstream stream(path.string());
    if (!stream.is_open()) {
        LOG_ERROR("Cannot open: {}", path);
        return;
    }

    std::string line;
    while (getline(stream, line))
    {
        if (line.rfind("vt", 0) == 0)
        {
            glm::vec2 uv;
            sscanf(line.c_str(), "vt %f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }
        else if (line.rfind("vn", 0) == 0) {
            glm::vec3 normal;
            sscanf(line.c_str(), "vn %f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if (line.rfind("v", 0) == 0)
        {
            glm::vec3 vertex;
            sscanf(line.c_str(), "v %f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_positions.push_back(vertex);
        }
        else if (line.rfind("f", 0) == 0)
        {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                LOG_ERROR("File can't be read by our simple parser");
                return;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
        else
        {
            // Probably a comment, eat up the rest of the line
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

Ref<Mesh> AssetManager::LoadTriangle()
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    LoadTriangle(vertices, indices);
    return CreateRef<Mesh>(vertices, indices);
}

Ref<Mesh> AssetManager::LoadAxis()
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    LoadAxis(vertices, indices);
    Ref<Mesh> mesh = CreateRef<Mesh>(vertices, indices);
    mesh->SetMode(DrawingMode::Lines);
    return mesh;
}

Ref<Mesh> AssetManager::LoadMesh(const std::filesystem::path& path)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    LoadOBJFile(path, vertices, indices);
    return CreateRef<Mesh>(vertices, indices);
}

Ref<Mesh> AssetManager::LoadQuad()
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    LoadQuad(vertices, indices);
    return CreateRef<Mesh>(vertices, indices);
}

Ref<Mesh> AssetManager::LoadSkyBox()
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    LoadSkyBox(vertices, indices);
    return CreateRef<Mesh>(vertices, indices);
}



}
