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

        Texture() = delete;
        Texture(const Texture&) = delete;

        Texture(int width, int height);
        Texture(const char* path);
        ~Texture();

        void Use();
        void UnBind();
    };
}

#endif 
