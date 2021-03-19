#include "Engine.hpp"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Rendering/Model.hpp"

#include "ECS/ECS.hpp"
#include "ECS/Systems/InputSystem.hpp"
#include "ECS/Systems/PhysicsSystem.hpp"
#include "ECS/Systems/PlayerControlSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"

#include "Inputs/InputHandler.hpp"

namespace BwatEngine {

    //initialization
    Engine::Engine()
    {

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

        ImGui_ImplGlfw_InitForOpenGL(context.window.window, false);
        ImGui_ImplOpenGL3_Init("#version 330");

        Coordinator::GetInstance()->Init();
        InitComponents(context);
        InitSystems(context);

        // time init var

        //Rendering::Model mymodel = Rendering::Model{ (std::string) "Assets/bag/backpack.obj" };
        model = Rendering::Model{ (std::string) "Assets/cube.obj" };

        InitSampleScene(context, model);
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

        //physicsSystem->Update(deltaTime);
        context.playerControlSystem->Update(context.deltaTime, context.window);
        
        context.MainFBO.UseAndBind();
        context.renderSystem->Update(context.deltaTime);
        context.MainFBO.Unbind();

        context.inputSystem->Update(context.deltaTime);

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

