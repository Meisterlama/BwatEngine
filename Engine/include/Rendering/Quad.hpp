#ifndef QUAD_HPP
#define QUAD_HPP

#include "Math/Vector/Vector2.hpp"

namespace Rendering
{
    class Quad
    {
    public:
        Quad();
        ~Quad();
        void Draw();

    private:
        unsigned int quadVAO, quadVBO;

    };
}

#endif //QUAD_HPP