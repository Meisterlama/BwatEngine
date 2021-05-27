#ifndef RENDERUI_HPP
#define RENDERUI_HPP

#include "Math/Math.hpp"
#include "Rendering/Quad.hpp"
#include <vector>

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
        Render2d(Rendering::Quad quad);
        ~Render2d();
        void Draw();
        std::vector<Image2D> images;

    };


}




#endif