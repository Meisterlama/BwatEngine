#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

//#include <assimp/Importer.hpp>      // C++ importer interface
//#include <assimp/scene.h>           // Output data structure
//#include <assimp/postprocess.h>     // Post processing flags

#define BMATH_IMPLEMENTATION
#include "Math/Math.hpp"

#include "Triangle.hpp"
#include "Window.hpp"
#include "Rendering/shader.hpp"
#include "Rendering/model.hpp"
#include "Rendering/camera.hpp"


int main()
{
	Bwat::Window mainWindow;

	// Init ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(mainWindow.window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Shader
	Rendering::Shader myShader("media/basic.vs", "media/basic.fs");
	Rendering::Model myModel((std::string)"media/bag/backpack.obj");

	// time init var
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// Camera init
	Rendering::Camera cam;

	float color[3] = { 0.5f, 0.5f, 0.5f };
	Rendering::Triangle myTri;

	while (mainWindow.IsWorking())
	{
		//Time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ColorEdit3("Clear color", color);

		// Depth Test and buffer
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, mainWindow.GetWidth(), mainWindow.GetHeight());
		glClearColor(color[0], color[1], color[2], 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Camera 
		cam.UseFreeFly(&mainWindow, deltaTime);

		// projection, view and model 
		BMath::Matrix4<float> projection = BMath::Matrix4<float>::CreatePerspective(60.f, mainWindow.GetWidth() / mainWindow.GetHeight(), 0.1f, 100.0f);
		BMath::Matrix4<float> view = cam.GetViewMatrix();
		BMath::Matrix4<float> model = BMath::Matrix4<float>::CreateScaleMat(1.f);

		//use shader 
		glUseProgram(myShader.ID);
		myShader.setMat4("proj", projection);
		myShader.setMat4("model", model);
		myShader.setMat4("view", view);

		//myTri.Update();
		myModel.Draw(myShader);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(mainWindow.window);
		glfwPollEvents();
	}

	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	mainWindow.Close();

	return 0;
}
