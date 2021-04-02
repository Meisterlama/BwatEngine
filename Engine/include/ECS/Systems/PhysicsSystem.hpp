#ifndef ENGINE_ECS_SYSTEMS_PHYSICS_HPP
#define ENGINE_ECS_SYSTEMS_PHYSICS_HPP

#include "ECS/System.hpp"

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
                Entity entity{ entityID };
                auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
                auto& transform = entity.GetComponent<TransformComponent>().transform;
                auto const& gravity = entity.GetComponent<GravityComponent>();

                transform.position += rigidBody.velocity * dt;
                rigidBody.velocity += gravity.force * dt;
            }
        };
    };
}

#endif //ENGINE_ECS_SYSTEMS_PHYSICS_HPP