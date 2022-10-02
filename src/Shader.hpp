#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <filesystem>

namespace OGLSample {

class Shader
{
public:
    Shader(const std::filesystem::path& path, GLuint type);
    ~Shader();
    GLuint GetId();
private:
    std::string read();
    void compile();
    GLuint m_Id;
    GLuint m_Type;
    std::filesystem::path m_Path;
};

class ShaderProgram
{
public:
    ShaderProgram(Shader& vertex, Shader& fragment);
    ~ShaderProgram();
    GLuint GetId();
private:
    void compile();
private:
    Shader& m_Vertex;
    Shader& m_Fragment;
    GLuint m_Id;
};

}

#endif
