
#include "OpenGL3Shader.hpp"
#include "FileSystem.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace OGLSample
{

OpenGL3Shader::OpenGL3Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    Compile(vertexPath, fragmentPath);
}

OpenGL3Shader::~OpenGL3Shader()
{
	glDeleteProgram(m_Id);
}

std::string OpenGL3Shader::LoadFile(const std::filesystem::path& path)
{
    std::string code;
    std::ifstream fileStream(path.c_str(), std::ios::in);
    if(!fileStream.is_open())
    {
        std::cerr << "Cannot open: " << path << "\n";
        return "";
    }
    std::stringstream stream;
    stream << fileStream.rdbuf();
    code = stream.str();
    fileStream.close();
    return code;
}

GLuint OpenGL3Shader::CompileShaderFile(const std::filesystem::path& path, GLuint type)
{
    const std::string content = LoadFile(path);

    if (content.size() == 0) {
        return 0;
    }

    GLuint shaderId = glCreateShader(type);

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
        std::cerr << "Error during shader (" << path << ") compilation: \n" << &errorLog[0];
        glDeleteShader(shaderId);

        assert(false && "Shader compilation failed");
    }

    return shaderId;

}

void OpenGL3Shader::CompileProgram(const GLuint vertexId, const GLuint fragmentId)
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
        std::cerr << "Error during program compilation (length: " << infoLogLength << "): \n" << msg << "\n";
        free(msg);
    }

    glDetachShader(m_Id, vertexId);
    glDeleteShader(vertexId);
    glDetachShader(m_Id, fragmentId);
    glDeleteShader(fragmentId);
}

void OpenGL3Shader::Compile(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    GLuint vertexId = CompileShaderFile(vertexPath, GL_VERTEX_SHADER);
    GLuint fragmentId = CompileShaderFile(fragmentPath, GL_FRAGMENT_SHADER);
    CompileProgram(vertexId, fragmentId);
}

uint32_t OpenGL3Shader::GetId()
{
    return m_Id;
}

void OpenGL3Shader::Bind()
{
    glUseProgram(m_Id);
}

void OpenGL3Shader::Unbind()
{
    glUseProgram(0);
}

void OpenGL3Shader::SetUniformInt(const std::string& name, const int value)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
    glUniform1i(location, value);
}

void OpenGL3Shader::SetUniformMat3(const std::string& name, const glm::mat3& matrix)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGL3Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGL3Shader::SetUniformVec4Array(const std::string& name, int count, const GLfloat* values)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
    glUniform4fv(location, count, values);
}

void OpenGL3Shader::SetUniformFloat(const std::string& name, const float value)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
    glUniform1f(location, value);
}

void OpenGL3Shader::SetUniformFloat2(const std::string& name, const glm::vec2& value)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
    glUniform2f(location, value.x, value.y);
}

void OpenGL3Shader::SetUniformFloat3(const std::string& name, const glm::vec3& value)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
	glUniform3f(location, value.x, value.y, value.z);
}

void OpenGL3Shader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
{
    GLint location = glGetUniformLocation(m_Id, name.c_str());
    if (location == -1)
        return;
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

}
