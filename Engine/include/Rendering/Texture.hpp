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
        unsigned int id;
        std::string type;
        std::string path;

        unsigned int TextureFromFile(const char* path, const std::string& directory);
        void GenerateTextureID(const char* path, const std::string& directory);
    };
}

#endif 
