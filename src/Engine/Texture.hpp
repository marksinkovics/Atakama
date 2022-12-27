#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <filesystem>

namespace OGLSample
{

class Texture
{
public:
    virtual uint32_t GetId() = 0;
    virtual void Bind(int index) = 0;
    virtual void Unbind() = 0;
    
    static Ref<Texture> Create(const std::filesystem::path& path);
    static Ref<Texture> Create(uint32_t id);
};

}

#endif
