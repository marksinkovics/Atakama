#ifndef OPENGL3_SHADER_BACKEND_HPP
#define OPENGL3_SHADER_BACKEND_HPP
 
#include "Engine/Shader.hpp"

namespace OGLSample {

class OpenGL3ShaderBackend: public ShaderBackend
{
public:
    OpenGL3ShaderBackend(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);

    virtual ~OpenGL3ShaderBackend();

    virtual uint32_t GetId() override;

    virtual void Bind() override;
    virtual void Unbind() override;

    virtual void SetUniformInt(const std::string& name, const int value) override;
    virtual void SetUniformMat3(const std::string& name, const glm::mat3& matrix) override;
    virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) override;
    virtual void SetUniformVec4Array(const std::string& name, int count, const float* values) override;
    virtual void SetUniformFloat(const std::string& name, const float value) override;
    virtual void SetUniformFloat2(const std::string& name, const glm::vec2& value) override;
    virtual void SetUniformFloat3(const std::string& name, const glm::vec3& value) override;
    virtual void SetUniformFloat4(const std::string& name, const glm::vec4& value) override;

private:
    std::string LoadFile(const std::filesystem::path& path);
    uint32_t CompileShaderFile(const std::filesystem::path& path, uint32_t type);
    void CompileProgram(const uint32_t vertexId, const uint32_t fragmentId);
    void Compile(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
private:
    uint32_t m_Id;
};

}

#endif
