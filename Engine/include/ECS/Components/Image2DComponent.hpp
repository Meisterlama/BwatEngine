#ifndef BWATENGINE_IMAGE2D_COMPONENT_Hpp
#define BWATENGINE_IMAGE2D_COMPONENT_Hpp

#include "Rendering/Texture.hpp"

namespace BwatEngine
{
    struct Image2DComponent
    {
        BwatEngine::Math::Vec2f position {50.f, 50.f};
        float rotation = 0.f;
        BwatEngine::Math::Vec2f scale {10.f, 10.f};
        Rendering::Texture* texture;
        bool isActive = false;

        void Use() { if (texture) texture->Use(); }
    };
}

#endif //BWATENGINE_IMAGE2D_COMPONENT_Hpp
