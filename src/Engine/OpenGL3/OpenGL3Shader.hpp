#ifndef OPENGL3_SHADER_HPP
#define OPENGL3_SHADER_HPP
 
#include "Engine/Shader.hpp"

#include <GL/glew.h>

namespace OGLSample {

class OpenGL3Shader: public Shader
{
public:
    OpenGL3Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);

    virtual ~OpenGL3Shader();

    virtual uint32_t GetId() override;

    virtual void Bind() override;
    virtual void Unbind() override;

    virtual void SetUniformInt(const std::string& name, const int value) override;
    virtual void SetUniformMat3(const std::string& name, const glm::mat3& matrix) override;
    virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) override;
    virtual void SetUniformVec4Array(const std::string& name, int count, const GLfloat* values) override;
    virtual void SetUniformFloat3(const std::string& name, const glm::vec3& value) override;
    virtual void SetUniformFloat4(const std::string& name, const glm::vec4& value) override;

private:
    std::string LoadFile(const std::filesystem::path& path);
    GLuint CompileShaderFile(const std::filesystem::path& path, GLuint type);
    void CompileProgram(const GLuint vertexId, const GLuint fragmentId);
    void Compile(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
private:
    uint32_t m_Id;
};

}

#endif
