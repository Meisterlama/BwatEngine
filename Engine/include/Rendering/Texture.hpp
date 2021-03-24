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
        enum class Type
        {
            E_DIFFUSE,
            E_SPECULAR,
            E_NORMAL,
            E_HEIGHT
        };
        unsigned int id;
        Type type;
        std::string path;

        //unsigned int TextureFromFile(const std::string& path);
        //void GenerateTextureID(const std::string& path);

        Texture(const std::string& path, Type type);
        ~Texture();
    };
}

#endif 
