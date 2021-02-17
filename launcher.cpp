#include <iostream>
#include <cstdio>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef BWATEDITOR

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// flag for the debug option allow to use logger if define.
//#define DEBUG

#include "Debug/Logger.hpp"

#endif //BWATEDITOR

#include "Math/Math.hpp"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags


typedef const char* (*glGetStringFunc)(int);

extern "C"
{
	//DLLEXPORT int NvOptimusEnablement = 1;
	//DLLEXPORT int AmdPowerXpressRequestHighPerformance = 1;
}

void debugGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	printf("GL error = %s\n", message);
}

void debugGLFWCallback(int error_code, const char* description)
{
	printf("GLFW error (%x) = %s\n", error_code, description);
}

GLFWwindow* InitGLFW()
{
	glfwInit();

	glfwSetErrorCallback(debugGLFWCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "TestEngine", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	return window;
}

void InitGlad()
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

int main()
{
	// init glfw
	GLFWwindow* window = InitGLFW();

	// init glad
	InitGlad();
#ifdef BWATEDITOR
	// Init ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
#endif

	float color[3] = { 0.8f, 0.2f, 0.2f };


	FILE *file;
	errno_t err;
	err = fopen_s(&file,"Log.txt", "w");

#ifdef BWATEDITOR
    BLogger::LogAddFp(file, 0);
    BLogger::LogDebug("test1");
#endif //BWATEDITOR

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

#ifdef BWATEDITOR
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ColorEdit3("Clear color", color);
#endif

		glClearColor(color[0], color[1], color[2], 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

#ifdef BWATEDITOR
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
		glfwSwapBuffers(window);
	}
#ifdef BWATEDITOR
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
#endif //BWATEDITOR

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
