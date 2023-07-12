#include "OBJImporter.hpp"

#include <sstream>

namespace Atakama
{

bool OBJImporter::Import(const std::filesystem::path& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    std::vector<uint32_t> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    //LOG_DEBUG("Loading OBJ from path: {}", path);

    std::ifstream stream(path.string());
    if (!stream.is_open()) {
        LOG_ERROR("Cannot open: {}", path);
        return false;
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
                return false;
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

    for (unsigned int i = 0; i < vertexIndices.size(); i++)
    {
        Vertex vertex{};

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        vertex.position = temp_positions[vertexIndex - 1];
        vertex.uv = { temp_uvs[uvIndex - 1].x, 1.f - temp_uvs[uvIndex - 1].y };
        vertex.normal = temp_normals[normalIndex - 1];

        if (uniqueVertices.count(vertex) == 0)
        {
            uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
            vertices.push_back(vertex);
        }

        indices.push_back(uniqueVertices[vertex]);
    }

    return true;
}

}