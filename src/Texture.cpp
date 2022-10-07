#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

namespace OGLSample
{

Texture::Texture(const std::filesystem::path& path)
{
    std::cerr << "Loading texture from path: " << path.c_str() << std::endl;
    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (data == NULL)
    {
        std::cerr << "Cannot load texture from path: " << path.c_str() << std::endl;
        stbi_image_free(data);
        return;
    }

    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

GLuint Texture::GetId()
{
    return m_Id;
}

void Texture::Bind(int index)
{
    int total_units;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &total_units);

    assert((index < total_units) && "Texture index is higher than the limit");
    glActiveTexture((GL_TEXTURE0 + index));
	glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Texture::Unbind()
{
    glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}