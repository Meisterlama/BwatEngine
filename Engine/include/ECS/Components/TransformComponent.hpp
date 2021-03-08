#ifndef ENGINE_ECS_COMPONENTS_TRANSFORM_HPP
#define ENGINE_ECS_COMPONENTS_TRANSFORM_HPP

#include "Math/Transform.hpp"

namespace BwatEngine
{
    struct TransformComponent
    {
        Math::Transform transform;
    };
}

#endif //ENGINE_ECS_COMPONENTS_TRANSFORM_HPP