#include "Texture.h"
#include <cassert>
#include <iostream>
#include <string>


Texture::Texture(const std::string& texturePath)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imageData = stbi_load(texturePath.c_str(), &m_width, &m_height,
        &m_numberOfChannels, 0);

    if (!imageData)
    {
        std::cout << "Couldn't load texture" << std::endl;
        assert(imageData);
    }

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    // Configure texture parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB,
        GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, m_id);
    stbi_image_free(imageData);
}

void Texture::Bind(size_t slot)const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::Unbind()const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}
