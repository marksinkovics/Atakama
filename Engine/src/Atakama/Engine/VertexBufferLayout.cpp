#include "VertexBufferLayout.hpp"

namespace Atakama
{

uint32_t VertexBufferElement::GetSize(enum Type type)
{
    switch (type)
    {
        case Type::Float:   return 4;
        case Type::Float2:  return 4 * 2;
        case Type::Float3:  return 4 * 3;
        case Type::Float4:  return 4 * 4;
        case Type::Mat3:    return 4 * 3 * 3;
        case Type::Mat4:    return 4 * 4 * 4;
        case Type::Int:     return 4;
        case Type::Int2:    return 4 * 2;
        case Type::Int3:    return 4 * 3;
        case Type::Int4:    return 4 * 4;
        case Type::Bool:    return 1;
        case Type::None:    return 0;
    }
}

uint32_t VertexBufferElement::GetComponentCount(enum Type type)
{
    switch (type)
    {
        case Type::Float:   return 1;
        case Type::Float2:  return 2;
        case Type::Float3:  return 3;
        case Type::Float4:  return 4;
        case Type::Mat3:    return 3;
        case Type::Mat4:    return 4;
        case Type::Int:     return 1;
        case Type::Int2:    return 2;
        case Type::Int3:    return 3;
        case Type::Int4:    return 4;
        case Type::Bool:    return 1;
        case Type::None:    return 0;
    }
}

VertexBufferElement::VertexBufferElement(enum Type type, const std::string& name, bool normalized)
: Type(type), Size(GetSize(type)), Offset(0), Normalized(normalized)
{
    
}



}
