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
        enum class Format
        {
            E_DIFFUSE,
            E_SPECULAR,
            E_NORMAL,
            E_HEIGHT
        };
      
        GLuint id;
        Format type;
        std::string path;

        Texture() = delete;
        Texture(const Texture&) = delete;

        Texture(const std::string& path, Format type);
        ~Texture();

        Texture(int width, int height);

        void Use();
        void UnBind();
    };
}

#endif 
