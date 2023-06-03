
#include "OpenGL3ShaderBackend.hpp"
#include <Atakama/Core/FileSystem.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace Atakama
{

OpenGL3ShaderBackend::OpenGL3ShaderBackend(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    Compile(vertexPath, fragmentPath);
}

OpenGL3ShaderBackend::~OpenGL3ShaderBackend()
{
	glDeleteProgram(m_Id);
}

std::string OpenGL3ShaderBackend::LoadFile(const std::filesystem::path& path)
{
    std::string code;
    std::ifstream fileStream(path.string());
    if(!fileStream.is_open())
    {
        LOG_ERROR("Cannot open shader: {}", path);
        return "";
    }
    std::stringstream stream;
    stream << fileStream.rdbuf();
    code = stream.str();
    return code;
}

uint32_t OpenGL3ShaderBackend::CompileShaderFile(const std::filesystem::path& path, uint32_t type)
{
    const std::string content = LoadFile(path);

    if (content.size() == 0) {
        return 0;
    }

    uint32_t shaderId = glCreateShader(type);

    const GLchar* contentPointer = content.c_str();
    glShaderSource(shaderId, 1, &contentPointer, NULL);
    glCompileShader(shaderId);

    GLint isCompiled = GL_FALSE;

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        int infoLogLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<GLchar> errorLog(infoLogLength);
        glGetShaderInfoLog(shaderId, infoLogLength, &infoLogLength, &errorLog[0]);
        LOG_ERROR("Error during shader ({}) compilation: {}", path, &errorLog[0]);
        glDeleteShader(shaderId);
    }

    return shaderId;

}

void OpenGL3ShaderBackend::CompileProgram(const uint32_t vertexId, const uint32_t fragmentId)
{
    m_Id = glCreateProgram();

    glAttachShader(m_Id, vertexId);
    glAttachShader(m_Id, fragmentId);

    glLinkProgram(m_Id);

    GLint result = GL_FALSE;
    int infoLogLength = 0;

    glGetShaderiv(m_Id, GL_LINK_STATUS, &result);
    glGetShaderiv(m_Id, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* msg = (char*)malloc(infoLogLength + 1);
        glGetProgramInfoLog(m_Id, infoLogLength, NULL, msg);
        LOG_ERROR("Error during program compilation (length: {}):\n {}", infoLogLength, msg);
        free(msg);
    }

    glDetachShader(m_Id, vertexId);
    glDeleteShader(vertexId);
    glDetachShader(m_Id, fragmentId);
    glDeleteShader(fragmentId);
}

void OpenGL3ShaderBackend::Compile(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    uint32_t vertexId = CompileShaderFile(vertexPath, GL_VERTEX_SHADER);
    uint32_t fragmentId = CompileShaderFile(fragmentPath, GL_FRAGMENT_SHADER);
    CompileProgram(vertexId, fragmentId);
}

uint32_t OpenGL3ShaderBackend::GetId()
{
    return m_Id;
}

void OpenGL3ShaderBackend::Bind()
{
    glUseProgram(m_Id);
}

void OpenGL3ShaderBackend::Unbind()
{
    glUseProgram(0);
}

void OpenGL3ShaderBackend::SetUniformInt(const std::string& name, const int value)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
    glUniform1i(location, value);
}

void OpenGL3ShaderBackend::SetUniformMat3(const std::string& name, const glm::mat3& matrix)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGL3ShaderBackend::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGL3ShaderBackend::SetUniformVec4Array(const std::string& name, int count, const GLfloat* values)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
    glUniform4fv(location, count, values);
}

void OpenGL3ShaderBackend::SetUniformFloat(const std::string& name, const float value)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
    glUniform1f(location, value);
}

void OpenGL3ShaderBackend::SetUniformFloat2(const std::string& name, const glm::vec2& value)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
    glUniform2f(location, value.x, value.y);
}

void OpenGL3ShaderBackend::SetUniformFloat3(const std::string& name, const glm::vec3& value)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
	glUniform3f(location, value.x, value.y, value.z);
}

void OpenGL3ShaderBackend::SetUniformFloat4(const std::string& name, const glm::vec4& value)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

}
