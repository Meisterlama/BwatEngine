#ifndef RENDERUI_HPP
#define RENDERUI_HPP

#include "Math/Math.hpp"
#include "Rendering/Quad.hpp"
#include <vector>
#include "glad/glad.h"
#include "Rendering/Shader.hpp"
#include "Rendering/Texture.hpp"


namespace Rendering
{

    struct Image2D
    {
        BwatEngine::Math::Vec2f position {0.1f, 0.1f};
        float rotation = 0.f;
        BwatEngine::Math::Vec2f scale {50.f, 50.f};
        Texture* tex = nullptr;
        bool isActive = false;

        void SetImagePos(const BwatEngine::Math::Vec2f& pos);
        void SetImageScale(const BwatEngine::Math::Vec2f& value);
        void SetImageRotation(float value);
        void SetIsActive(bool value);

    };

    class Render2d
    {
    public:

        Render2d();
        Render2d(Rendering::Quad quad);
        ~Render2d();
        void Draw(BwatEngine::Math::Mat4f view, BwatEngine::Math::Mat4f proj);
        std::vector<Image2D*> images;
        Rendering::Quad usedQuad;
        Rendering::Shader shader;


    };


}




#endif