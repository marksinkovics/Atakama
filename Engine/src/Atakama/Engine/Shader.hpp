#ifndef ATAKAMA_SHADER_HPP
#define ATAKAMA_SHADER_HPP

namespace Atakama {

class ShaderBackend
{
public:
    virtual ~ShaderBackend() = default;

    virtual uint32_t GetId() = 0;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    virtual void SetUniformInt(const std::string& name, int value) = 0;
    virtual void SetUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
    virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
    virtual void SetUniformVec4Array(const std::string& name, int count, const float* values) = 0;
    virtual void SetUniformFloat(const std::string& name, const float value) = 0;
    virtual void SetUniformFloat2(const std::string& name, const glm::vec2& value) = 0;
    virtual void SetUniformFloat3(const std::string& name, const glm::vec3& value) = 0;
    virtual void SetUniformFloat4(const std::string& name, const glm::vec4& value) = 0;

    static Ref<ShaderBackend> Create(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
};

class SubMesh;

class Shader
{
public:
    Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
    virtual ~Shader();
    virtual uint32_t GetId();

    virtual void Bind();
    virtual void Bind(Ref<SubMesh>& subMesh);
    virtual void Unbind();

    virtual void SetUniformInt(const std::string& name, int value);
    virtual void SetUniformMat3(const std::string& name, const glm::mat3& matrix);
    virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
    virtual void SetUniformVec4Array(const std::string& name, int count, const float* values);
    virtual void SetUniformFloat(const std::string& name, const float value);
    virtual void SetUniformFloat2(const std::string& name, const glm::vec2& value);
    virtual void SetUniformFloat3(const std::string& name, const glm::vec3& value);
    virtual void SetUniformFloat4(const std::string& name, const glm::vec4& value);
protected:
    Ref<ShaderBackend> m_ShaderBackend;
};

}

#endif
