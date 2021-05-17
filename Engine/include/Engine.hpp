#ifndef ENGINE_HPP
#define ENGINE_HPP


#include "Window.hpp"
#include "Scene.hpp"
#include "Rendering/FrameBuffer.hpp"

namespace BwatEngine
{

	class Engine
	{
	public:
		Engine();
		~Engine();

		void Update();
		void Close();

		bool ShouldRun() { return window.IsWorking(); };

		Scene& GetScene() { return scene; }
		const Scene& GetScene() const { return scene; }

		Window& GetWindow() { return window; }
		const Window& GetWindow() const { return window; }

		GLFWwindow* GetGLFWwindow() { return window.handler; };


		bool isPlaying = false;

	private:
		float lastFrame = 0.0f;

		Window window;
		Scene scene;

		void RenderScene();

	};

}
#endif // !ENGINE_HPP
