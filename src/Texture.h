#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <string>

class Texture
{
private:
    unsigned int m_id;

    int m_width;
    int m_height;
    int m_numberOfChannels;
public:
    Texture(const std::string& texturePath);
    void Bind(size_t slot=0)const;
    void Unbind()const;
    ~Texture();
};