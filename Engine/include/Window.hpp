#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace BwatEngine
{

	class Window
	{
	public:
		Window();
		~Window(); // rule of three -> https://en.cppreference.com/w/cpp/language/rule_of_three

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
