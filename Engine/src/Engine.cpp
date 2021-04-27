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
#include "ECS/Systems/PhysicsSystem.hpp"
#include "ECS/Systems/PlayerControlSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Systems/ScriptSystem.hpp"
#include "ECS/Systems/SoundSystem.hpp"
#include "ECS/Systems/PostProcessSystem.hpp"

#include "Inputs/InputHandler.hpp"

using namespace BwatEngine;

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

    InputHandler::Initialize(GetGLFWwindow());
}

//Main Funtion of engine 
void Engine::Update()
{
    InputHandler::Update();

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
    {
        updateAudio = !updateAudio;
    }

    if (updatePhysics)
    {
        scene.physicsSystem->Update();
    }

    scene.playerControlSystem->Update(Time::deltaTime, GetGLFWwindow());

    ManageRenderAndPostProcess();

    if (updateAudio)
    {
        scene.soundSystem->Update();
    }

    static bool updateScript = false;
    if (InputHandler::GetKeyboardDown(KEY_F4))
    {
        LogDebug("ScriptOn");
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


void Engine::ManageRenderAndPostProcess()
{
    bool isPostProcess = false;

    if (isPostProcess)
        scene.renderSystem->BindMainRenderFBO();
    else
        MainFBO->UseAndBind();

    scene.renderSystem->Update(GetWindow());

    if (isPostProcess)
    {
        // Post Process ... 
        MainFBO->UseAndBind();
        scene.postProcessSystem->Update(scene.renderSystem->GetRenderTextureID(), POSTPROCESS_SHADER::INVERSION);
    }

    glDisable(GL_FRAMEBUFFER_SRGB);
    MainFBO->Unbind();
}