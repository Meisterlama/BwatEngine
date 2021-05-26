#ifndef QUAD_HPP
#define QUAD_HPP

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