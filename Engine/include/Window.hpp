#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Bwat
{

	class Window
	{
	public:
		Window();
		~Window();

		void SetUp();
		void Close();

		GLFWwindow* window = nullptr;

		float GetHeight() { return height; };
		float GetWidth() { return width; };
		bool IsWorking() { return !glfwWindowShouldClose(window); };

	private:

		float width = 0.f;
		float height = 0.f;

	};

}