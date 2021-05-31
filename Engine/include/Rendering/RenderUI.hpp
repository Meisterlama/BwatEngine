#ifndef RENDERUI_HPP
#define RENDERUI_HPP

#include "Math/Math.hpp"
#include "Rendering/Quad.hpp"
#include <vector>
#include "glad/glad.h"
#include "Rendering/Shader.hpp"


namespace Rendering
{
    class Texture;
    struct Image2D
    {
        BwatEngine::Math::Vec2f position {0.f, 0.f};
        BwatEngine::Math::Vec2f rotation {0.f, 0.f};
        BwatEngine::Math::Vec2f scale {1.f, 1.f};
        Texture* tex = nullptr;
        bool isActive = false;

        /* class or struct */

    };

    class Render2d
    {
    public:

        Render2d();
        Render2d(Rendering::Quad quad);
        ~Render2d();
        void Draw(GLuint gameTexture);
        std::vector<Image2D> images;
        Rendering::Quad usedQuad;
        Rendering::Shader shader;


    };


}




#endif