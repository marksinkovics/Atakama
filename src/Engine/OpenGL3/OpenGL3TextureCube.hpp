#ifndef ATAKAMA_OPENGL3_TEXTURE_CUBE_HPP
#define ATAKAMA_OPENGL3_TEXTURE_CUBE_HPP

#include "Engine/Texture.hpp"

namespace Atakama
{

class OpenGL3TextureCube: public TextureCube
{
public:
    OpenGL3TextureCube();
    OpenGL3TextureCube(std::array<std::filesystem::path, 6> paths);
    OpenGL3TextureCube(uint32_t id);
    ~OpenGL3TextureCube();
    uint32_t GetId();
    void Bind(int index);
    void Unbind();
private:
    uint32_t m_Id;
    int m_TotalUnits;
};

}


#endif
