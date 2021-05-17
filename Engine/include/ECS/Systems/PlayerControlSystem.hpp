#ifndef ENGINE_ECS_SYSTEMS_PLAYER_CONTROL_HPP
#define ENGINE_ECS_SYSTEMS_PLAYER_CONTROL_HPP

#include "Math/Vector/Vector3.hpp"
#include "ECS/System.hpp"

namespace BwatEngine
{
    class PlayerControlSystem: public System
    {
        bool lockMouse = false;
        Math::Vec3f rotation{};
    public:

        virtual void Update() override;
    };
}

#endif //ENGINE_ECS_SYSTEMS_PLAYER_CONTROL_HPP