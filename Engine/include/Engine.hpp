#ifndef ENGINE_HPP
#define ENGINE_HPP


#include "Window.hpp"
#include <memory>

#include "Rendering/Model.hpp"
#include "Rendering/FrameBuffer.hpp"
#include "ECS/Entity.hpp"

#include "Physic/Physic.hpp"

namespace BwatEngine
{

	struct Context
	{
		Window window{};

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		Rendering::FrameBufferObject MainFBO;

		Scene scene{};
	};

	class Engine
	{

	public:

		Engine();
		~Engine();

		void Update();
		void Close();

		bool ShouldRun() { return context.window.IsWorking(); };

		static Context& GetContext() { return context; };

	private:

	};

}
#endif // !ENGINE_HPP
