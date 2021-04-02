#ifndef ENGINE_ECS_SYSTEMS_INPUTS_HPP
#define ENGINE_ECS_SYSTEMS_INPUTS_HPP

#include "ECS/System.hpp"
#include "Inputs/InputHandler.hpp"

namespace BwatEngine
{
    class InputsSystem : public System
    {
    public:
        void Init(GLFWwindow* window)
        {
            BwatEngine::InputHandler::Initialize(window);
        }

        void Update(float dt)
        {
            BwatEngine::InputHandler::Update();
        };
    };
}

#endif //ENGINE_ECS_SYSTEMS_INPUTS_HPP