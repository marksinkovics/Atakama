#include "Shader.hpp"
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
    compile();
}

Shader::~Shader()
{
    glDeleteShader(m_Id);
}

std::string Shader::read() 
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

void Shader::compile()
{
    const std::string content = read();
    std::cout << "Compile shader: " << m_Path << "\n";

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

ShaderProgram::ShaderProgram(Shader& vertex, Shader& fragment)
    : m_Vertex(vertex), m_Fragment(fragment)
{
    m_Id = glCreateProgram();
    compile();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_Id);
}

void ShaderProgram::compile()
{

    std::cout << "Linking program\n";

    glAttachShader(m_Id, m_Vertex.GetId());
    glAttachShader(m_Id, m_Fragment.GetId());
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

    glDetachShader(m_Id, m_Vertex.GetId());
    glDetachShader(m_Id, m_Fragment.GetId());
}

GLuint ShaderProgram::GetId()
{
    return m_Id;
}

}
