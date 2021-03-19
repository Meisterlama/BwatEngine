#ifndef ENGINE_ECS_SYSTEMS_PHYSICS_HPP
#define ENGINE_ECS_SYSTEMS_PHYSICS_HPP

#include "ECS/System.hpp"
#include "ECS/Components/RigidBodyComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/GravityComponent.hpp"

namespace BwatEngine
{
    class PhysicsSystem : public System
    {
    public:
        void Init() {};

        void Update(float dt) 
        {
            for (auto entityID : entities)
            {
                auto coordinator = Coordinator::GetInstance();
                auto& rigidBody = coordinator->GetComponent<RigidBodyComponent>(entityID);
                auto& transform = coordinator->GetComponent<TransformComponent>(entityID).transform;
                auto const& gravity = coordinator->GetComponent<GravityComponent>(entityID);

                transform.position += rigidBody.velocity * dt;
                rigidBody.velocity += gravity.force * dt;
            }
        };
    };
}

#endif //ENGINE_ECS_SYSTEMS_PHYSICS_HPP