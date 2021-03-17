#include "Engine.hpp"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Math/Math.hpp"
#include "Scene.hpp"

#include "Rendering/Shader.hpp"
#include "Rendering/Light.hpp"
#include "Rendering/Camera.hpp"
#include "EditorInterface.hpp"

#include "ECS/Systems/InputSystem.hpp"
#include "ECS/Systems/PhysicsSystem.hpp"
#include "ECS/Systems/PlayerControlSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"


namespace BwatEngine {

    //initialization
    Engine::Engine()
    {
        GetContext() = {};

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

        ImGui_ImplGlfw_InitForOpenGL(context.window.window, false);
        ImGui_ImplOpenGL3_Init("#version 330");

        
    }

    Engine::~Engine()
    {
    }

    //Main Funtion of engine 
    void Engine::Update()
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Time
        float currentFrame = glfwGetTime();
        context.deltaTime = currentFrame - context.lastFrame;
        context.lastFrame = currentFrame;

        ImGui::Begin("bonjour");

        ImGui::Text("bonjor");
        ImGui::End();

        //physicsSystem->Update(deltaTime);
        context.scene.playerControlSystem->Update(context.deltaTime, context.window);
        
        context.MainFBO.UseAndBind();
        context.scene.renderSystem->Update();
        context.MainFBO.Unbind();

        context.scene.inputSystem->Update(context.deltaTime);

        //ImGui::Render();
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(context.window.window);
        
    }


    //Close all content 
    void Engine::Close()
    {
        ImGui_ImplGlfw_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
        context.window.Close();
    }
}

