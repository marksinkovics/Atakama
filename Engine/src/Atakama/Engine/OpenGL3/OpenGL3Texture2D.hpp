#ifndef ATAKAMA_OPENGL3_TEXTURE_2D_HPP
#define ATAKAMA_OPENGL3_TEXTURE_2D_HPP

#include "Atakama/Engine/Texture.hpp"

namespace Atakama
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
    GLenum m_InternalFormat;
    GLenum m_DataFormat;
};

}

#endif
