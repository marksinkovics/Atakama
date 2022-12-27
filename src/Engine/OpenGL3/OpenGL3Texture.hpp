#ifndef OPENGL3_TEXTURE_HPP
#define OPENGL3_TEXTURE_HPP

#include "Engine/Texture.hpp"

namespace OGLSample
{

class OpenGL3Texture: public Texture
{
public:
    OpenGL3Texture(const std::filesystem::path& path);
    OpenGL3Texture(uint32_t id);
    ~OpenGL3Texture();
    uint32_t GetId();
    void Bind(int index);
    void Unbind();
private:
    uint32_t m_Id;
    int m_TotalUnits;
};

}

#endif
