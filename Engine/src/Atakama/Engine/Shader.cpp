#include "Shader.hpp"
#include "RenderTypes.hpp"
#include "Atakama/Engine/OpenGL3/OpenGL3ShaderBackend.hpp"

namespace Atakama
{

Ref<ShaderBackend> ShaderBackend::Create(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    switch(g_RuntimeGlobalContext.m_GraphicsAPI)
    {
        case GraphicsAPI::None:
        {
            LOG_FATAL("GraphicsAPI::None is not supported!");
            break;
        }
        case GraphicsAPI::OpenGL3: return CreateRef<OpenGL3ShaderBackend>(vertexPath, fragmentPath);
    }
}


Shader::Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    m_ShaderBackend = ShaderBackend::Create(vertexPath, fragmentPath);
}

Shader::~Shader()
{
    m_ShaderBackend.reset();
}

uint32_t Shader::GetId()
{
    return m_ShaderBackend->GetId();
}

void Shader::Bind()
{
    return m_ShaderBackend->Bind();
}

void Shader::Bind(Ref<SubMesh>& subMesh)
{
    m_ShaderBackend->Bind();
}

void Shader::Unbind()
{
    return m_ShaderBackend->Unbind();
}

void Shader::SetUniformInt(const std::string& name, int value)
{
    return m_ShaderBackend->SetUniformInt(name, value);
}

void Shader::SetUniformMat3(const std::string& name, const glm::mat3& value)
{
    return m_ShaderBackend->SetUniformMat3(name, value);
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& value)
{
    return m_ShaderBackend->SetUniformMat4(name, value);
}

void Shader::SetUniformVec4Array(const std::string& name, int count, const float* values)
{
    return m_ShaderBackend->SetUniformVec4Array(name, count, values);
}

void Shader::SetUniformFloat(const std::string& name, const float value)
{
    return m_ShaderBackend->SetUniformFloat(name, value);
}

void Shader::SetUniformFloat2(const std::string& name, const glm::vec2& value)
{
    return m_ShaderBackend->SetUniformFloat2(name, value);
}

void Shader::SetUniformFloat3(const std::string& name, const glm::vec3& value)
{
    return m_ShaderBackend->SetUniformFloat3(name, value);
}

void Shader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
{
    return m_ShaderBackend->SetUniformFloat4(name, value);
}



}
