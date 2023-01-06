#include "OpenGL3TextureCube.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

namespace OGLSample
{

OpenGL3TextureCube::OpenGL3TextureCube()
{
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_TotalUnits);
}

OpenGL3TextureCube::OpenGL3TextureCube(std::array<std::filesystem::path, 6> paths)
{
    LOG_DEBUG("Loading TextureCube");

    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_Id);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < paths.size(); i++)
    {
        unsigned char *data = stbi_load(paths[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            LOG_ERROR("Cubemap tex failed to load at path:: {}", paths[i]);
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_TotalUnits);
}

OpenGL3TextureCube::OpenGL3TextureCube(uint32_t id)
{
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_TotalUnits);

}

OpenGL3TextureCube::~OpenGL3TextureCube()
{

}

uint32_t OpenGL3TextureCube::GetId()
{
    return m_Id;
}

void OpenGL3TextureCube::Bind(int index)
{
    ASSERT((index < m_TotalUnits) && "Texture index is higher than the limit");
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_Id);
}

void OpenGL3TextureCube::Unbind()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

}
