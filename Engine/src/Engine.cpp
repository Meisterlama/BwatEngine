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
#include "ECS/Systems/SoundSystem.hpp"

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

        static bool updatePhysics = false;
        if (InputHandler::GetKeyboardDown(KEY_F2))
        {
            updatePhysics = !updatePhysics;
                    
        }
        static bool updateAudio = false;
        if (InputHandler::GetKeyboardDown(KEY_F3))
            updateAudio = !updateAudio;

        if (updatePhysics)
        {
            scene.physicsSystem->Update();
        }

        scene.playerControlSystem->Update(Time::deltaTime, GetGLFWwindow());
        
        if (MainFBO)
            MainFBO->UseAndBind();

         scene.renderSystem->Update(GetWindow());

        if (updateAudio)
        {
            scene.soundSystem->Update();
        }
         if (MainFBO)
            MainFBO->Unbind();

        scene.inputSystem->Update();

        static bool updateScript = false;
        if (InputHandler::GetKeyboardDown(KEY_F4))
        {
            updateScript = !updateScript;

        }
        if (updateScript)
        {
            scene.scriptSystem->Update();
        }

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

