#include "Texture.hpp"

#include <iostream>

namespace OGLSample
{

uint32_t loadBMP(const std::filesystem::path& path, uint8_t** data, uint32_t* width, uint32_t* height)
{

    std::cout << "Loading BMP image from path: " << path << "\n";

    uint8_t header[54];
    uint32_t dataPos;
    uint32_t imageSize;

    FILE* file = fopen(path.c_str(), "rb");
    if(!file)
    {
        std::cerr << "Path " << path << " could not be opened.\n";
        return 0;
    }

    if (fread(header, 1, 54, file) != 54)
    {
        std::cerr << "Not a correct BPM file\n";
        fclose(file);
        return 0;
    }

    if (header[0] != 'B' || header[1] != 'M')
    {
        std::cerr << "Not a correct BPM file\n";
        fclose(file);
        return 0;
    }

    if (*(uint32_t*)&(header[0x1E]) != 0)
    {
        std::cerr << "Not a correct BPM file\n";
        fclose(file);
        return 0;
    }


    if (*(uint32_t*)&(header[0x1C]) != 24)
    {
        std::cerr << "Not a correct BPM file\n";
        fclose(file);
        return 0;
    }

    dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	*width = *(int*)&(header[0x12]);
	*height = *(int*)&(header[0x16]);

    if (imageSize == 0)
    {
        imageSize = (*width) * (*height) * 3;
    }

    if (dataPos == 0)
    {
        dataPos=54;
    }

    *data = new uint8_t[imageSize];

    fread(*data, 1, imageSize, file);

    fclose(file);

    return imageSize;
}

Texture::Texture(const std::filesystem::path& path)
{
    uint8_t *data = nullptr;
    uint32_t width, height;
    uint32_t status = loadBMP(path, &data, &width, &height);
    if (status == 0)
    {
        std::cerr << "Texture loading failed, status = " << status << "\n";
        free(data);
        return;
    }

    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    // free(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

GLuint Texture::GetId()
{
    return m_Id;
}

void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Id);
}

}