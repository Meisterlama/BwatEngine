#ifndef ENGINE_ECS_SYSTEMS_PHYSICS_HPP
#define ENGINE_ECS_SYSTEMS_PHYSICS_HPP

#include "ECS/System.hpp"

#include "ECS/Components/GravityComponent.hpp"
#include "ECS/Components/RigidBodyComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/PlayerComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"

namespace BwatEngine
{
    class PhysicsSystem : public System
    {
    public:
        void Init() {};

        void Update() 
        {
            for (auto entityID : entities)
            {
                Entity entity{ entityID };
                auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
                auto& transform = entity.GetComponent<TransformComponent>().transform;
                auto const& gravity = entity.GetComponent<GravityComponent>();

                transform.position += rigidBody.velocity * Engine::GetContext().deltaTime;
                rigidBody.velocity += gravity.force * Engine::GetContext().deltaTime;
            }
        };
    };
}

#endif //ENGINE_ECS_SYSTEMS_PHYSICS_HPP