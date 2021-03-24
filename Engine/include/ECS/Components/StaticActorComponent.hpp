#ifndef ENGINE_ECS_COMPONENTS_STATIC_ACTOR_HPP
#define ENGINE_ECS_COMPONENTS_STATIC_ACTOR_HPP

#include "Math/Vector/Vector3.hpp"
#include "Math/Transform.hpp"
#include "Physic/Physic.hpp"
#include <PxPhysicsAPI.h>
#include "Physic/PhysicCast.hpp"

namespace BwatEngine
{
    struct StaticActorComponent
    {
        StaticActorComponent() = default;

        StaticActorComponent(const Math::Transform& transform)
        {
            staticActor = Physic::GetPhysics()->createRigidStatic(ToPxTransform(transform));
        };

        physx::PxRigidStatic* staticActor = nullptr;
    };
}

#endif //ENGINE_ECS_COMPONENTS_RIGID_BODY_HPP