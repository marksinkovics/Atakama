#include "OpenGL3Texture2D.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Atakama
{

OpenGL3Texture2D::OpenGL3Texture2D()
    : m_Id(-1), m_TotalUnits(0), m_InternalFormat(0), m_DataFormat(0)
{
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_TotalUnits);
}

OpenGL3Texture2D::OpenGL3Texture2D(const std::filesystem::path& path)
    : m_Id(-1), m_TotalUnits(0), m_InternalFormat(0), m_DataFormat(0)
{
    LOG_DEBUG("Loading Texture2D from path: {}", path)

    int width, height, channels;
    unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);

    if (data == NULL)
    {
        LOG_ERROR("Cannot load texture from path: {}", path);
        stbi_image_free(data);
        return;
    }

    if (channels == 4)
    {
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;
    }
    else if (channels == 3)
    {
        m_InternalFormat = GL_RGB8;
        m_DataFormat = GL_RGB;
    }

    assert((m_InternalFormat & m_DataFormat) && "Format not supported");

    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, width, height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_TotalUnits);
}

OpenGL3Texture2D::OpenGL3Texture2D(uint32_t id)
: m_Id(id), m_TotalUnits(0), m_InternalFormat(0), m_DataFormat(0)
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

    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

void OpenGL3Texture2D::Unbind()
{
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

}
