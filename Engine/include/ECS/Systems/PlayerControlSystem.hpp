#ifndef ENGINE_ECS_SYSTEMS_PLAYER_CONTROL_HPP
#define ENGINE_ECS_SYSTEMS_PLAYER_CONTROL_HPP

#include "Math/Common.hpp"
#include "ECS/System.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "Inputs/InputHandler.hpp"
#include "imgui.h"


#include "AL/al.h"

namespace BwatEngine
{
    class PlayerControlSystem: public System
    {
        bool lockMouse = false;
        Math::Vec3f rotation{};
    public:
        void Init()
        {};

        void Update(float dt, GLFWwindow *win);
    };
}

#endif //ENGINE_ECS_SYSTEMS_PLAYER_CONTROL_HPP