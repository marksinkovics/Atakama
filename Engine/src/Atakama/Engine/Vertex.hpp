#ifndef ATAKAMA_VERTEX_HPP
#define ATAKAMA_VERTEX_HPP

#include "Atakama/Engine/VertexBuffer.hpp"
#include "Atakama/Engine/IndexBuffer.hpp"
#include "Atakama/Engine/VertexArray.hpp"

namespace Atakama
{

struct Vertex
{
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
    glm::vec3 color {1.0f, 1.0f, 1.0f};

    bool operator==(const Vertex &other) const;

    static VertexBufferLayout GetLayout();
};
}

namespace std
{
    template<>
    struct hash<Atakama::Vertex>
    {
        size_t operator()(const Atakama::Vertex &vertex) const
        {
            size_t seed = 0;
            Atakama::hashCombine(seed, vertex.position, vertex.color, vertex.normal, vertex.uv);
            return seed;
        }
    };
}


#endif
