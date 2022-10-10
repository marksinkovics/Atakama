#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <filesystem>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OGLSample
{

class Texture
{
public:
    Texture(const std::filesystem::path& path);
    GLuint GetId();
    void Bind(int index);
    void Unbind();
private:
    GLuint m_Id;
    int m_TotalUnits;
};

}

#endif