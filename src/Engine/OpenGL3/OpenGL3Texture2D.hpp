#ifndef OPENGL3_TEXTURE_2D_HPP
#define OPENGL3_TEXTURE_2D_HPP

#include "Engine/Texture.hpp"

namespace OGLSample
{

class OpenGL3Texture2D: public Texture2D
{
public:
    OpenGL3Texture2D();
    OpenGL3Texture2D(const std::filesystem::path& path);
    OpenGL3Texture2D(uint32_t id);
    ~OpenGL3Texture2D();
    uint32_t GetId();
    void Bind(int index);
    void Unbind();
private:
    uint32_t m_Id;
    int m_TotalUnits;
};

}

#endif
