#include "AssetLibrary.hpp"

#include "Atakama/Engine/Mesh.hpp"

namespace Atakama 
{

Ref<Mesh> AssetLibrary::LoadTriangle()
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    std::vector<Vertex> rawVertices {
        {{-0.5f, -0.5f, 0.0f}, { 0.f, 0.f }, { 0.f, 0.f, 1.f }, { 1.0f, 0.0f, 0.0f }},
        { { 0.5f, -0.5f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 1.f}, { 0.0f, 1.0f, 0.0f} },
        { { 0.0f,  0.5f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 1.f}, { 0.0f, 0.0f, 1.0f} },
    };

    AssetLibrary::GenerateIndices(rawVertices, vertices, indices);
    return CreateRef<Mesh>(vertices, indices);
}

Ref<Mesh> AssetLibrary::LoadAxis()
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;


    std::vector<Vertex> rawVertices {
        {{0.0f, 0.0f, 0.0f}, { 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 1.0f, 0.0f, 0.0f }},
        { {3.0f, 0.0f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {1.0f, 0.0f, 0.0f} },
        { {0.0f, 0.0f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {0.0f, 1.0f, 0.0f} },
        { {0.0f, 3.0f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {0.0f, 1.0f, 0.0f} },
        { {0.0f, 0.0f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {0.0f, 0.0f, 1.0f} },
        { {0.0f, 0.0f, 3.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f}, {0.0f, 0.0f, 1.0f} },
    };

    AssetLibrary::GenerateIndices(rawVertices, vertices, indices);

    Ref<Mesh> mesh = CreateRef<Mesh>(vertices, indices);
    mesh->SetMode(DrawingMode::Lines);
    return mesh;
}

Ref<Mesh> AssetLibrary::LoadQuad()
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    std::vector<Vertex> rawVertices {
        {{-1.0f, 1.0f, 0.0f}, { 0.0f, 1.0f }, { 0.f, 0.f, 1.f }, { 1.0f, 0.0f, 1.0f }},
        { {-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {0.f, 0.f, 1.f}, { 1.0f, 0.0f, 1.0f} },
        { { 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, {0.f, 0.f, 1.f}, { 1.0f, 0.0f, 1.0f} },

        { {-1.0f,  1.0f, 0.0f}, {0.0f, 1.0f}, {0.f, 0.f, 1.f}, { 0.0f, 1.0f, 1.0f} },
        { { 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, {0.f, 0.f, 1.f}, { 0.0f, 1.0f, 1.0f} },
        { { 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f}, {0.f, 0.f, 1.f}, { 0.0f, 1.0f, 1.0f} }
    };

    AssetLibrary::GenerateIndices(rawVertices, vertices, indices);

    return CreateRef<Mesh>(vertices, indices);
}

Ref<Mesh> AssetLibrary::LoadSkyBox()
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    std::vector<Vertex> rawVertices {
        {{-1.0f, 1.0f, -1.0f}, { 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }},
        { {-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { {-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },

        { {-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { {-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { {-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { {-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { {-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { {-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },

        { { 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },

        { {-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { {-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { {-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },

        { {-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { {-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { {-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },

        { {-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { {-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { {-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { { 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} }
    };

    AssetLibrary::GenerateIndices(rawVertices, vertices, indices);
    return CreateRef<Mesh>(vertices, indices);
}

Ref<Mesh> AssetLibrary::LoadGrid()
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    std::vector<Vertex> rawVertices {
        { { 1.0, 0.0, 1.0}, { 0.0f, 0.0f }, { 0.f, 0.f, 1.f }, { 1.0f, 0.0f, 1.0f } },
        { {  1.0, 0.0, -1.0}, {1.0f, 0.0f}, {0.f, 0.f, 1.f }, { 1.0f, 0.0f, 1.0f } },
        { { -1.0, 0.0, -1.0}, {0.0f, 1.0f}, {0.f, 0.f, 1.f }, { 0.0f, 1.0f, 1.0f } },

        { {-1.0, 0.0, -1.0}, {0.0f, 1.0f}, { 0.f, 0.f, 1.f }, { 0.0f, 1.0f, 1.0f } },
        { {-1.0, 0.0,  1.0}, {0.0f, 1.0f}, { 0.f, 0.f, 1.f }, { 0.0f, 1.0f, 1.0f } },
        { { 1.0, 0.0,  1.0}, {0.0f, 0.0f}, { 0.f, 0.f, 1.f }, { 1.0f, 0.0f, 1.0f } },

    };

    AssetLibrary::GenerateIndices(rawVertices, vertices, indices);

    return CreateRef<Mesh>(vertices, indices);
}

void AssetLibrary::GenerateIndices(std::vector<Vertex>& input, std::vector<Vertex>& output, std::vector<uint32_t>& indices)
{
    std::unordered_map<Vertex, uint32_t> uniqueVertices {};

    for (Vertex& vertex : input)
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