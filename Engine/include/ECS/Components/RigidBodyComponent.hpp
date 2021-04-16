#ifndef ENGINE_ECS_COMPONENTS_RIGID_BODY_HPP
#define ENGINE_ECS_COMPONENTS_RIGID_BODY_HPP

#include "Physic/RigidBody.hpp"

namespace BwatEngine
{
    struct RigidBodyComponent
    {
        RigidBody* rigidBody = nullptr;
    };
}

#endif //ENGINE_ECS_COMPONENTS_RIGID_BODY_HPP