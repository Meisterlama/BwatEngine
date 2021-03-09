#ifndef ENGINE_HPP
#define ENGINE_HPP


#include "Window.hpp"
#include <memory>

#include "Rendering/Model.hpp"


namespace BwatEngine
{
	class InputsSystem;
	class PhysicsSystem;
	class PlayerControlSystem;
	class RenderSystem;
	
	

	class Engine
	{

	public:

		Engine();
		~Engine();

		void Update();
		void Close();

		Window window;
		Rendering::Model model;

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		std::shared_ptr<InputsSystem> inputSystem = nullptr;
		std::shared_ptr<PhysicsSystem> physicsSystem = nullptr;
		std::shared_ptr<PlayerControlSystem> playerControlSystem = nullptr;
		std::shared_ptr<RenderSystem> renderSystem = nullptr;

	private:

	};

}
#endif // !ENGINE_HPP
