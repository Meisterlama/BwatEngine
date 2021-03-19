#ifndef ENGINE_ECS_COMPONENTS_RIGID_BODY_HPP
#define ENGINE_ECS_COMPONENTS_RIGID_BODY_HPP

#include "Math/Vector/Vector3.hpp"
#include "Math/Transform.hpp"
#include <PxPhysicsAPI.h>

namespace BwatEngine
{
    struct RigidBodyComponent
    {
        RigidBodyComponent(const Math::Transform& transform)
        {
            rigidBody = Physic::GetPhysics()->createRigidDynamic(*(physx::PxTransform*) & transform);
        };

        physx::PxRigidDynamic* rigidBody;
    };
}

#endif //ENGINE_ECS_COMPONENTS_RIGID_BODY_HPP