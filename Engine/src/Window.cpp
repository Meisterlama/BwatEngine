#include "Window.hpp"
#include <cstdio>
#include <iostream>

using namespace BwatEngine;

Window::Window()
{
	//Define size of window
	width = 1200;
	height = 720;

	// init context
	window = InitGLFW();
	InitGlad();
}

Window::~Window()
{
}

typedef const char* (*glGetStringFunc)(int);

void debugGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	printf("GL error = %s\n", message);
}

void debugGLFWCallback(int error_code, const char* description)
{
	printf("GLFW error (%x) = %s\n", error_code, description);
}

GLFWwindow* Window::InitGLFW()
{
	glfwInit();

	glfwSetErrorCallback(debugGLFWCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "TestEngine", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	return window;
}

void Window::InitGlad()
{
	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

	std::cout << " RENDERER = " << glGetString(GL_RENDERER) << std::endl;
	std::cout << " VENDOR = " << glGetString(GL_VENDOR) << std::endl;
	std::cout << " VERSION = " << glGetString(GL_VERSION) << std::endl;

	// Setup KHR_debug callback
	if (GLAD_GL_KHR_debug)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback((GLDEBUGPROC)debugGLCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_PERFORMANCE, GL_DONT_CARE, 0, nullptr, GL_FALSE);
		glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 0, nullptr, GL_FALSE);
	}
}

void Window::Close()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
