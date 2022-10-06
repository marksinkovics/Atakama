#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <filesystem>
#include <memory>

namespace OGLSample {

class Shader
{
public:
    Shader(const std::filesystem::path& path, GLuint type);
    Shader(Shader&& shader) = default;
    ~Shader();
    GLuint GetId();
private:
    std::string Read();
    void Compile();
    GLuint m_Id;
    GLuint m_Type;
    std::filesystem::path m_Path;
};

class ShaderProgram
{
public:
    ShaderProgram(Ref<Shader>& vertex, Ref<Shader>& fragment);
    ShaderProgram(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
    ~ShaderProgram();
    GLuint GetId();
    void Bind();

    void SetUniformInt(const std::string& name, const int value);
    void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

private:
    void Compile();
private:
    Ref<Shader> m_Vertex;
    Ref<Shader> m_Fragment;
    GLuint m_Id;
};

}

#endif
