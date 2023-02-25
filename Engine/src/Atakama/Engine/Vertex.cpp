#include "Vertex.hpp"

namespace Atakama
{

bool Vertex::operator==(const Vertex &other) const
{
    return
        position == other.position &&
        color == other.color &&
        normal == other.normal &&
        uv == other.uv;
}

VertexBufferLayout Vertex::GetLayout()
{
    return {
        { VertexBufferElement::Type::Float3, "aPosition"},
        { VertexBufferElement::Type::Float2, "aUV"},
        { VertexBufferElement::Type::Float3, "aNormal"},
        { VertexBufferElement::Type::Float3, "aColor"},
    };
}

}
