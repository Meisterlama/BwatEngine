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
      
        GLuint id; // texture id being public is not safe
        Type type;
        std::string path;

        Texture() = delete;
        Texture(const Texture&) = delete;

        Texture(const std::string& path, Type type);
        ~Texture(); // rule of three -> https://en.cppreference.com/w/cpp/language/rule_of_three

        Texture(int width, int height);

        void Use();
        void UnBind();
    };
}

#endif 
