#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace BwatEngine
{

	class Window
	{
	public:
		Window();
		~Window();

		void Close();
		GLFWwindow* InitGLFW();
		void InitGlad();

		GLFWwindow* handler = nullptr;

		float GetHeight() { return height; };
		float GetWidth() { return width; };
		bool IsWorking() { return !glfwWindowShouldClose(handler); };

	private:

		float width = 0.f;
		float height = 0.f;

	};

}