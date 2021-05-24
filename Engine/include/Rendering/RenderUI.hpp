#ifndef RENDERUI_HPP
#define RENDERUI_HPP

#include "Math/Math.hpp"

namespace Rendering
{
    class Texture;
    class Image2D
    {
        BwatEngine::Math::Vec2f position;
        BwatEngine::Math::Vec2f rotation;
        BwatEngine::Math::Vec2f scale;
        Texture* tex;

        /* class or struct */

    };
}




#endif