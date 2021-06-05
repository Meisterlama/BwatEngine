#ifndef RENDERUISYSTEM_HPP
#define RENDERUISYSTEM_HPP

#include "ECS/System.hpp"
#include "ECS/ECS.hpp"


#include "Rendering/RenderUI.hpp"
#include "Rendering/FrameBuffer.hpp"
#include "Ecs/Components/CameraComponent.hpp"
#include "Ecs/Components/TransformComponent.hpp."


namespace BwatEngine
{

    class RenderUISystem : public System
    {
    private:

        Rendering::Render2d render;
        Math::Mat4f view;
        Math::Mat4f proj;



    public:

        bool isRenderUI = true;
        RenderUISystem();

        virtual void Update() override;
        void SetCamMatrix(CameraComponent& camComp, TransformComponent & camTransform);

        Rendering::Image2D* CreateImage(const char* textPath);
        void SetImagePos(Math::Vec2f pos);
        void SetImageScale(Math::Vec2f scale);
        void SetImageRotation(float rotation);
        void SetIsActive(bool isActive);

    };
}


#endif // RENDERUISYSTEM_HPP
