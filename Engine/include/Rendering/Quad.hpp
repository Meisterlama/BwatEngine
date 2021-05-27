#ifndef QUAD_HPP
#define QUAD_HPP

#include "Math/Vector/Vector2.hpp"

namespace Rendering
{
    class Quad
    {
    public:
        Quad(BwatEngine::Math::Vec2f screenSize, BwatEngine::Math::Vec2f pointA, BwatEngine::Math::Vec2f pointB);
        ~Quad();
        void Draw();

    private:
        unsigned int quadVAO, quadVBO;

    };
}

#endif //QUAD_HPP