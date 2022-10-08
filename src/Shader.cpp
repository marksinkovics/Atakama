#include "Shader.hpp"
#include "FileSystem.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace OGLSample
{

Shader::Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    Compile(vertexPath, fragmentPath);
}

Shader::~Shader()
{
	glDeleteProgram(m_Id);
}

std::string Shader::LoadFile(const std::filesystem::path& path)
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

GLuint Shader::CompileShaderFiles(const std::filesystem::path& path, GLuint type)
{
    const std::string content = LoadFile(path);

    if (content.size() == 0) {
        return 0;
    }

    GLuint shaderId = glCreateShader(type);

    const GLchar* contentPointer = content.c_str();
    glShaderSource(shaderId, 1, &contentPointer, NULL);
    glCompileShader(shaderId);

    GLint result = GL_FALSE;
    int infoLogLength = 0;

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* msg = (char*)malloc(infoLogLength + 1);
        glGetShaderInfoLog(m_Id, infoLogLength, NULL, msg);
        std::cerr << "Error during shader compilation: \n" << msg << "\n";
        free(msg);
    }

    return shaderId;

}

void Shader::CompileProgram(const GLuint vertexId, const GLuint fragmentId)
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

void Shader::Compile(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    GLuint vertexId = CompileShaderFiles(vertexPath, GL_VERTEX_SHADER);
    GLuint fragmentId = CompileShaderFiles(fragmentPath, GL_FRAGMENT_SHADER);
    CompileProgram(vertexId, fragmentId);
}

GLuint Shader::GetId()
{
    return m_Id;
}

void Shader::Bind()
{
    glUseProgram(m_Id);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::SetUniformInt(const std::string& name, const int value)
{
    GLuint location = glGetUniformLocation(m_Id, name.c_str());
    glUniform1i(location, value);
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
    GLuint location = glGetUniformLocation(m_Id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}


}
