#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace OGLSample {

class Shader
{
public:
    Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);

    ~Shader();

    GLuint GetId();

    void Bind();
    void Unbind();

    void SetUniformInt(const std::string& name, const int value);
    void SetUniformMat3(const std::string& name, const glm::mat3& matrix);
    void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
    void SetUniformVec4Array(const std::string& name, int count, const GLfloat* values);
    void SetUniformFloat3(const std::string& name, const glm::vec3& value);
    void SetUniformFloat4(const std::string& name, const glm::vec4& value);

private:
    std::string LoadFile(const std::filesystem::path& path);
    GLuint CompileShaderFile(const std::filesystem::path& path, GLuint type);
    void CompileProgram(const GLuint vertexId, const GLuint fragmentId);
    void Compile(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
private:
    GLuint m_Id;
};

}

#endif
