#include "Window.hpp"
#include "Debug/Logger.hpp"

using namespace BwatEngine;

Window::Window()
{
	//Define size of window
	width = 1200;
	height = 720;

	// init context
	handler = InitGLFW();
	InitGlad();
}

Window::~Window()
{
}

typedef const char* (*glGetStringFunc)(int);

void debugGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	LogError("GL error = %s\n", message);
}

void debugGLFWCallback(int error_code, const char* description)
{
    LogError("GLFW error (%x) = %s\n", error_code, description);
}

GLFWwindow* Window::InitGLFW()
{
	glfwInit();

	glfwSetErrorCallback(debugGLFWCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "BwatEngine", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	return window;
}

void Window::InitGlad()
{
	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

    LogInfo("RENDERER = %s", glGetString(GL_RENDERER));
    LogInfo("VENDOR = %s", glGetString(GL_VENDOR));
    LogInfo("VERSION = %s", glGetString(GL_VERSION));

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
	glfwDestroyWindow(handler);
	glfwTerminate();
}
