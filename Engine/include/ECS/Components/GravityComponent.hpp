#ifndef ENGINE_ECS_COMPONENTS_GRAVITY_HPP
#define ENGINE_ECS_COMPONENTS_GRAVITY_HPP

#include "Math/Vector/Vector3.hpp"

namespace BwatEngine
{
    struct GravityComponent
    {
        Math::Vec3f force;
    };
}

#endif //ENGINE_ECS_COMPONENTS_GRAVITY_HPP