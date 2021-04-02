
#include "Rendering/Texture.hpp"
#include "Debug/Logger.hpp"


using namespace Rendering;

Texture::Texture(int width, int height)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(const std::string& path, Type type) : path(path), type(type)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(1);

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;

        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path.c_str() << std::endl;
        stbi_image_free(data);
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

void Texture::Use()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}