#ifndef ENGINE_ECS_SYSTEMS_INPUTS_HPP
#define ENGINE_ECS_SYSTEMS_INPUTS_HPP

#include "ECS/System.hpp"
#include "Inputs/InputHandler.hpp"
#include "Engine.hpp"
#include "Window.hpp"

namespace BwatEngine
{
    class InputsSystem : public System
    {
    public:
				// why are you defining these functions in .hpp instead of in .cpp ?
        void Init(Window& window)
        {
            BwatEngine::InputHandler::Initialize(window.handler);
        }

        void Update()
        {
            BwatEngine::InputHandler::Update();
        };
    };
}

#endif //ENGINE_ECS_SYSTEMS_INPUTS_HPP
