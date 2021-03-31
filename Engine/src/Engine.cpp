#include "Engine.hpp"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Math/Math.hpp"
#include "Scene.hpp"

#include "Rendering/Shader.hpp"
#include "Rendering/Light.hpp"
#include "Rendering/Camera.hpp"
#include "EditorInterface.hpp"

#include "ECS/ECS.hpp"
#include "ECS/Systems/InputSystem.hpp"
#include "ECS/Systems/PhysicsSystem.hpp"
#include "ECS/Systems/PlayerControlSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Systems/ScriptSystem.hpp"

#include "Inputs/InputHandler.hpp"

namespace BwatEngine {

    //initialization
    Engine::Engine() : scene(window)
    {

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

        ImGui_ImplGlfw_InitForOpenGL(GetGLFWwindow(), false);
        ImGui_ImplOpenGL3_Init("#version 330");

    }

    //Main Funtion of engine 
    void Engine::Update()
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        float currentFrame = glfwGetTime();
        Time::deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        scene.physicsSystem->Update();
        scene.playerControlSystem->Update(Time::deltaTime, GetGLFWwindow());
        
        if (MainFBO)
            MainFBO->UseAndBind();

         scene.renderSystem->Update(GetWindow());

         if (MainFBO)
            MainFBO->Unbind();

        scene.inputSystem->Update();
        
        // if game running update script
        scene.scriptSystem->Update();

        glfwSwapBuffers(GetGLFWwindow());
        
    }

    //Close all content 
    void Engine::Close()
    {
        ImGui_ImplGlfw_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
        GetWindow().Close();
    }

    Engine::~Engine()
    {

    }
}

