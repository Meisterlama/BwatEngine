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
#include "Rendering/light.hpp"
#include "World.hpp"
#include "ECS/ComponentModel.hpp"


int main()
{
	Bwat::Window mainWindow;

	// Init ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(mainWindow.window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Shader
	Rendering::Shader myShader("Assets/basic.vs", "Assets/basic.fs");
	Rendering::Shader myShaderLight("Assets/basic.vs", "Assets/multilight.fs");
	Rendering::Model myModel((std::string)"Assets/bag/backpack.obj");

	// time init var
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// Camera init
	Rendering::Camera cam;

	float color[3] = { 0.5f, 0.5f, 0.5f };
	Rendering::Triangle myTri;

	// Light, Next we need manage light on a lights manager or on scene graph ... WIP
	std::vector<Rendering::Light*> lights;

	Rendering::Light mylight(Rendering::TYPE_LIGHT::Directional, { 0.1f,0.1f,0.5f }, { 0.1f,0.1f,0.5f }, { 0.1f,0.1f,0.5f });

	lights.push_back(&mylight);
	
	// myWorld
	World  myWorld(&myShaderLight);

	ComponentModel myNewModel((std::string)"Assets/bag/backpack.obj");

	Entity myEntity;
	myEntity.AddComponent(&myNewModel);

	myWorld.AddEntity(&myEntity);
	myWorld.AddLight(&mylight);

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
		//debug Light
		ImGui::ColorEdit3("light ambient", lights[0]->ambient.values);
		ImGui::DragFloat3("posLight", lights[0]->position.values);
		ImGui::DragFloat3("dirLight", lights[0]->direction.values);
		ImGui::DragFloat("cutOff", &lights[0]->cutoff);
		ImGui::DragFloat("outerCutOff", &lights[0]->outerCutoff);

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
		myShaderLight.use();
		myShaderLight.setMat4("proj", projection);
		myShaderLight.setMat4("model", model);
		myShaderLight.setMat4("view", view);
		myShaderLight.setVec3("viewPos", cam.cameraPos.X, cam.cameraPos.Y, cam.cameraPos.Z);

		myWorld.UpdateEntities();
		//myTri.Update();
		//myModel.Draw(myShaderLight,lights);

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
