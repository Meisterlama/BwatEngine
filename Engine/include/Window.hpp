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

		int GetHeight() { return height; };
		int GetWidth() { return width; };
		bool IsWorking() { return !glfwWindowShouldClose(handler); };

	private:

		int width = 0.f;
		int height = 0.f;

	};

}