#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <stb_image.h>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Rendering
{
    struct Texture
    {
        GLuint id;
        std::string type;
        std::string path;

        unsigned int TextureFromFile(const char* path, const std::string& directory);
        void GenerateTextureID(const char* path, const std::string& directory);

        void GenerateTexture(float width, float height, GLenum format = GL_RGBA, unsigned char* data = nullptr);

        void GenTexture();
        void BindTexture();
        void UnbindTexture();
        void TextureParameter();
        void TextureImage(float width, float height, GLenum format = GL_RGBA, unsigned char* data = nullptr);
    };
}

#endif 
