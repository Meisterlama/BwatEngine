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
				// These are not exactly 'Type' of textures
				// It describe how they are used in your shader
				// prefer using an enum "Format" which describe
				// what data your texture contains (ie. R, RG, RGB)
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
