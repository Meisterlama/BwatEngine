
#include "Rendering/texture.hpp"
#include "Debug/Logger.hpp"


using namespace Rendering;

Texture::Texture(const std::string& path, Type type)
    : path(path)
    , type(type)
{
    glGenTextures(1, &id);

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

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        TextureParameter();

        stbi_image_free(data);
    }
    else
    {
        LogError("Texture failed to load at path: %s\n", path.c_str());
        stbi_image_free(data);
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
}
/*
void Texture::GenerateTextureID(const std::string& path)
{
    std::string filename = std::string(path);
    //filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        TextureParameter();

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    id = textureID;
}*/

void Texture::GenerateTexture(float width, float height, GLenum format, unsigned char* data)
{
    GenTexture();
    BindTexture();
    TextureParameter();
    TextureImage(width, height, format, data);
    UnbindTexture();
}

void Texture::GenTexture()
{
    glGenTextures(1, &id);
}

void Texture::BindTexture()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::UnbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::TextureParameter()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::TextureImage(float width, float height, GLenum format, unsigned char* data)
{
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
}
