#ifndef ENGINE_ECS_COMPONENTS_RIGID_BODY_HPP
#define ENGINE_ECS_COMPONENTS_RIGID_BODY_HPP

#include "Math/Vector/Vector3.hpp"

namespace BwatEngine
{
    struct RigidBodyComponent
    {
        Math::Vec3f velocity;
        Math::Vec3f acceleration;
    };
}

#endif //ENGINE_ECS_COMPONENTS_RIGID_BODY_HPP