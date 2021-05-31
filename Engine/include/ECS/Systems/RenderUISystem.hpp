#ifndef RENDERUISYSTEM_HPP
#define RENDERUISYSTEM_HPP

#include "ECS/System.hpp"
#include "ECS/ECS.hpp"


#include "Rendering/RenderUI.hpp"
#include "Rendering/FrameBuffer.hpp"


namespace BwatEngine
{

    class RenderUISystem : public System
    {
    private:
        Rendering::Quad quad;
        Rendering::Render2d render;
        Rendering::FrameBufferObject framebuffer;

        Rendering::Texture* text;

    public:

        bool isRenderUI = true;
        RenderUISystem(int width, int height);

        virtual void Update() override;
        void Begin();
    };
}


#endif // RENDERUISYSTEM_HPP
