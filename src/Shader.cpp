#include "Shader.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace OGLSample
{

Shader::Shader(const std::filesystem::path& path, GLuint type)
    : m_Path(path), m_Type(type)
{
    m_Id = glCreateShader(m_Type);
    Compile();
}

Shader::~Shader()
{
    glDeleteShader(m_Id);
}

std::string Shader::Read()
{
    std::string code;
    std::ifstream fileStream(m_Path.c_str(), std::ios::in);
    if(!fileStream.is_open())
    {
        std::cerr << "Cannot open: " << m_Path << "\n";
        return "";
    }
    std::stringstream stream;
    stream << fileStream.rdbuf();
    code = stream.str();
    fileStream.close();
    return code;
}

void Shader::Compile()
{
    const std::string content = Read();

    const GLchar* contentPointer = content.c_str();
    glShaderSource(m_Id, 1, &contentPointer, NULL);
    glCompileShader(m_Id);

    GLint result = GL_FALSE;
    int infoLogLength = 0;

    glGetShaderiv(m_Id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(m_Id, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        char* msg = (char*)malloc(infoLogLength + 1);
        glGetShaderInfoLog(m_Id, infoLogLength, NULL, msg);
        std::cerr << "Error during shader compilation: \n" << msg << "\n";
        free(msg);
    }
}

GLuint Shader::GetId()
{
   return m_Id;
}

ShaderProgram::ShaderProgram(Ref<Shader>& vertex, Ref<Shader>& fragment)
    : m_Vertex(vertex), m_Fragment(fragment)
{
    m_Id = glCreateProgram();
    Compile();
}

ShaderProgram::ShaderProgram(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    Ref<Shader> vertexShader = CreateRef<Shader>(vertexPath, GL_VERTEX_SHADER);
    Ref<Shader> fragmentShader = CreateRef<Shader>(fragmentPath, GL_FRAGMENT_SHADER);
    ShaderProgram(vertexShader, fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_Id);
}

void ShaderProgram::Compile()
{
    glAttachShader(m_Id, m_Vertex->GetId());
    glAttachShader(m_Id, m_Fragment->GetId());
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

    glDetachShader(m_Id, m_Vertex->GetId());
    glDetachShader(m_Id, m_Fragment->GetId());
}

GLuint ShaderProgram::GetId()
{
    return m_Id;
}

void ShaderProgram::Bind()
{
    glUseProgram(m_Id);
}

void ShaderProgram::SetUniformInt(const std::string& name, const int value)
{
    GLuint location = glGetUniformLocation(m_Id, name.c_str());
    glUniform1i(location, value);
}

void ShaderProgram::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
    GLuint location = glGetUniformLocation(m_Id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}


}
