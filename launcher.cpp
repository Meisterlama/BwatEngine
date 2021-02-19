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

#include "Editor/include/EditorInterface.hpp"


int main()
{
	Bwat::Window mainWindow;
	EditorInterface editor;

	editor.InitImGui(mainWindow);
#endif

	// Shader
	Rendering::Shader myShader("basic.vs", "basic.fs");
	Rendering::Model myModel((std::string)"media/bag/backpack.obj");

	// time init var
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// Camera init
	Rendering::Camera cam;

	float color[3] = { 0.5f, 0.2f, 0.5f };
	Rendering::Triangle myTri;

	while (mainWindow.IsWorking())
	{
		//Time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//ImGui
		editor.CreateFrame()

		ImGui::ColorEdit3("Clear color", color);
#endif

		// Depth Test and buffer
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, mainWindow.GetWidth(), mainWindow.GetHeight());
		glClearColor(color[0], color[1], color[2], 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Camera 
		cam.usefreefly(&mainWindow, deltaTime);

		// projection, view and model 
		BMath::Matrix4<float> projection = BMath::Matrix4<float>::CreatePerspective(60.f, mainWindow.GetWidth() / mainWindow.GetHeight(), 0.1f, 100.0f);
		BMath::Matrix4<float> view = cam.ViewOfCamera();
		BMath::Matrix4<float> model = BMath::Matrix4<float>::CreateScaleMat(1.f);

		//use shader 
		glUseProgram(myShader.ID);
		myShader.setMat4("proj", projection);
		myShader.setMat4("model", model);
		myShader.setMat4("view", view);

		//myTri.Update();
		myModel.Draw(myShader);

#ifdef BWATEDITOR
		editor.RenderImGui();

		glfwSwapBuffers(mainWindow.window);
		glfwPollEvents();
	}
#ifdef BWATEDITOR
	editor.DestroyImGui();

	mainWindow.Close();

	return 0;
}
