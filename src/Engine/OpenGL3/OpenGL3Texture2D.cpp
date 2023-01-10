#include "OpenGL3Texture2D.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace OGLSample
{

OpenGL3Texture2D::OpenGL3Texture2D()
{
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_TotalUnits);
}

OpenGL3Texture2D::OpenGL3Texture2D(const std::filesystem::path& path)
{
    LOG_DEBUG("Loading Texture2D from path: {}", path)

    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (data == NULL)
    {
        LOG_ERROR("Cannot load texture from path: {}", path);
        stbi_image_free(data);
        return;
    }

    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_TotalUnits);
}

OpenGL3Texture2D::OpenGL3Texture2D(uint32_t id)
: m_Id(id)
{
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_TotalUnits);
}

OpenGL3Texture2D::~OpenGL3Texture2D()
{
    glDeleteTextures(1, &m_Id);
}

uint32_t OpenGL3Texture2D::GetId()
{
    return m_Id;
}

void OpenGL3Texture2D::Bind(int index)
{
    ASSERT((index < m_TotalUnits) && "Texture index is higher than the limit");

    glActiveTexture((GL_TEXTURE0 + index));
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

void OpenGL3Texture2D::Unbind()
{
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

}