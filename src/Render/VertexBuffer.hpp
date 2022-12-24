#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OGLSample
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
    
    static uint32_t GetSize(Type type)
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
    
    static uint32_t GetComponentCount(Type type)
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
    
    static GLenum GetOpenGLBaseType(Type type)
    {
        switch (type)
        {
            case Type::Float:   return GL_FLOAT;
            case Type::Float2:  return GL_FLOAT;
            case Type::Float3:  return GL_FLOAT;
            case Type::Float4:  return GL_FLOAT;
            case Type::Mat3:    return GL_FLOAT;
            case Type::Mat4:    return GL_FLOAT;
            case Type::Int:     return GL_INT;
            case Type::Int2:    return GL_INT;
            case Type::Int3:    return GL_INT;
            case Type::Int4:    return GL_INT;
            case Type::Bool:    return GL_BOOL;
            case Type::None:    return 0;
        }
    }

    
    std::string Name;
    Type Type;
    uint32_t Size;
    size_t Offset;
    bool Normalized;
    
    VertexBufferElement() = default;
    VertexBufferElement(enum Type type, const std::string& name, bool normalized = false)
    : Type(type), Size(GetSize(type)), Offset(0), Normalized(normalized)
    {}
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
    uint32_t m_Stride;
};

class VertexBuffer
{
public:
    VertexBuffer(uint32_t size);
    VertexBuffer(float* vertices, uint32_t size);
    
    virtual ~VertexBuffer();
    
    virtual void Bind() const;
    virtual void Unbind() const;
    
    virtual void SetData(const void* data, uint32_t size);
    
    virtual uint32_t GetCount();
    
    virtual VertexBufferLayout& GetLayout();
    virtual void SetLayout(const VertexBufferLayout& layout);
private:
    uint32_t m_Id;
    VertexBufferLayout m_Layout;
    uint32_t m_Size;
};

class IndexBuffer
{
public:
    IndexBuffer(uint32_t* indices, uint32_t count);
    virtual ~IndexBuffer();
    virtual void Bind() const;
    virtual void Unbind() const;
    virtual uint32_t GetCount() const;
private:
    uint32_t m_Id;
    uint32_t m_Count;
};

class VertexArray
{
public:
    VertexArray();
    virtual ~VertexArray();
    virtual void Bind() const;
    virtual void Unbind() const;

    virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);
    
    virtual uint32_t GetVertexCount();
    
    virtual std::vector<Ref<VertexBuffer>>& GetVertexBuffers();
    virtual Ref<IndexBuffer> GetIndexBuffer();
private:
    uint32_t m_Id;
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;
    Ref<IndexBuffer> m_IndexBuffer;
    uint32_t m_VertexBufferIndex;
};

}

#endif
