#ifndef RENDERUISYSTEM_HPP
#define RENDERUISYSTEM_HPP

#include "Rendering/QuadScreen.hpp"
#include "Rendering/Shader.hpp"
#include "ECS/System.hpp"
#include "ECS/ECS.hpp"


namespace BwatEngine
{

    class RenderUISystem : public System
    {
    private:
        Math::Mat4f view;
        Math::Mat4f proj;

        Rendering::FullScreenQuad usedQuad;
        Rendering::Shader shader;

    public:

        bool isRenderUI = true;
        RenderUISystem();

        virtual void Update() override;
    };
}


#endif // RENDERUISYSTEM_HPP
