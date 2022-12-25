#ifndef SHADER_HPP
#define SHADER_HPP

namespace OGLSample {

class Shader
{
public:
    virtual ~Shader() = default;

    virtual uint32_t GetId() = 0;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void SetUniformInt(const std::string& name, const int value) = 0;
    virtual void SetUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
    virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
    virtual void SetUniformVec4Array(const std::string& name, int count, const GLfloat* values) = 0;
    virtual void SetUniformFloat3(const std::string& name, const glm::vec3& value) = 0;
    virtual void SetUniformFloat4(const std::string& name, const glm::vec4& value) = 0;

    static Ref<Shader> Create(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
};

}

#endif
