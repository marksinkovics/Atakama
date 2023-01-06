#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <filesystem>
#include <array>

namespace OGLSample
{

class Texture
{
public:
    virtual uint32_t GetId() = 0;
    virtual void Bind(int index) = 0;
    virtual void Unbind() = 0;
};

class Texture2D: public Texture
{
public:
    static Ref<Texture> Create();
    static Ref<Texture> Create(const std::filesystem::path& path);
    static Ref<Texture> Create(uint32_t id);
};

class TextureCube: public Texture
{
public:
    static Ref<Texture> Create();
    static Ref<Texture> Create(const std::array<std::filesystem::path, 6>& paths);
    static Ref<Texture> Create(uint32_t id);
};

}

#endif
