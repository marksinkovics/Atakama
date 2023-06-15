#ifndef ATAKAMA_VERTEX_BUFFER_LAYOUT_HPP
#define ATAKAMA_VERTEX_BUFFER_LAYOUT_HPP

namespace Atakama
{

struct VertexBufferElement
{
    enum class Type {
        None = 0,
        Float, Float2, Float3, Float4,
        Mat3, Mat4,
        Int, Int2, Int3, Int4,
        Bool
    };
    
    static uint32_t GetSize(enum Type type);
    static uint32_t GetComponentCount(enum Type type);
    
    std::string Name;
    Type Type;
    uint32_t Size;
    size_t Offset;
    bool Normalized;
    
    VertexBufferElement() = default;
    VertexBufferElement(enum Type type, const std::string& name, bool normalized = false);
};

class VertexBufferLayout
{
public:
    VertexBufferLayout() {}
    VertexBufferLayout(std::initializer_list<VertexBufferElement> elements)
    : m_Elements(elements)
    {
        CalculateOffsetsAndStride();
    }
    uint32_t GetStride() const { return m_Stride; }
    const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }

    std::vector<VertexBufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<VertexBufferElement>::iterator end() { return m_Elements.end(); }
    std::vector<VertexBufferElement>::const_iterator begin() const { return m_Elements.begin(); }
    std::vector<VertexBufferElement>::const_iterator end() const { return m_Elements.end(); }
private:
    void CalculateOffsetsAndStride()
    {
        size_t offset = 0;
        m_Stride = 0;
        for (auto& element : m_Elements)
        {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }
private:
    std::vector<VertexBufferElement> m_Elements;
    uint32_t m_Stride { 0 };
};

}

#endif
