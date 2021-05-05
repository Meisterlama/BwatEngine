#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <stb_image.h>
#include <vector>

#include "glad/glad.h"

namespace Rendering
{
    struct Texture
    {
        enum class Type
        {
            E_DIFFUSE,
            E_SPECULAR,
            E_NORMAL,
            E_HEIGHT,

        };
      
        GLuint id;
        Type type;
        std::string path;

        Texture() = delete;
        Texture(const Texture&) = delete;

        Texture(const std::string& path, Type type);
        ~Texture();

        Texture(int width, int height);

        void Resize(int width, int height);
        void Use();
        void UnBind();
    };
}

#endif 
