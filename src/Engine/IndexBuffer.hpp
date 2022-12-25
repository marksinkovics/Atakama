#ifndef INDEX_BUFFER_HPP
#define INDEX_BUFFER_HPP

namespace OGLSample
{

class IndexBuffer
{
public:
    virtual ~IndexBuffer() = default;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual uint32_t GetCount() const = 0;
    
    static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
};

}

#endif
