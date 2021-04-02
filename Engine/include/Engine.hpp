#ifndef ENGINE_HPP
#define ENGINE_HPP


#include "Window.hpp"
#include <memory>

#include "Rendering/Model.hpp"
#include "Rendering/FrameBuffer.hpp"
#include "Core.hpp"

#include "ECS/Coordinator.hpp"

namespace BwatEngine
{
	class InputsSystem;
	class PhysicsSystem;
	class PlayerControlSystem;
	class RenderSystem;

	struct Context
	{
		Window window{};

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		Rendering::FrameBufferObject MainFBO;

        std::shared_ptr<InputsSystem> inputSystem = nullptr;
        std::shared_ptr<PhysicsSystem> physicsSystem = nullptr;
        std::shared_ptr<PlayerControlSystem> playerControlSystem = nullptr;
        std::shared_ptr<RenderSystem> renderSystem = nullptr;

        std::vector<Entity> entities;
    };

	class Engine
	{

	public:

		Engine();
		~Engine();

		void Update();
		void Close();

		Context context;

		Rendering::Model model;

		bool ShouldRun() { return context.window.IsWorking(); };


	private:

	};

}
#endif // !ENGINE_HPP
