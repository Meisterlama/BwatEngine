#ifndef ENGINE_ECS_COMPONENTS_RIGID_BODY_HPP
#define ENGINE_ECS_COMPONENTS_RIGID_BODY_HPP

#include "Math/Vector/Vector3.hpp"
#include "Math/Transform.hpp"
#include "Physic/Physic.hpp"
#include <PxPhysicsAPI.h>
#include "Physic/PhysicCast.hpp"

namespace BwatEngine
{
    struct RigidBodyComponent
    {
        RigidBodyComponent(const Math::Transform& transform = {})
        {
            rigidBody = Physic::GetPhysics()->createRigidDynamic(ToPxTransform(transform));
        };

        physx::PxRigidDynamic* rigidBody = nullptr;
    };
}

#endif //ENGINE_ECS_COMPONENTS_RIGID_BODY_HPP