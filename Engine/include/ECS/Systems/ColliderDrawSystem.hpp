#ifndef ENGINE_ECS_SYSTEMS_COLLIDER_DRAW_HPP
#define ENGINE_ECS_SYSTEMS_COLLIDER_DRAW_HPP

#include "ECS/System.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/Primitives.hpp"

namespace BwatEngine
{

    class ColliderDrawSystem : public System
    {
        Rendering::Shader shader;
        Rendering::Model cube;
        Rendering::Model sphere;

        EntityID cameraID;
        Signature signature;
    public:

        ColliderDrawSystem();
        virtual void Update() override;
        void DrawWithCamera(const CameraComponent& camera, const TransformComponent& cameraTransform);

    private:

        void CheckCameraValid();
    };
}

#endif //ENGINE_ECS_SYSTEMS_COLLIDER_DRAW_HPP