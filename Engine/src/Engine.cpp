#include "Engine.hpp"

#include "ECS/Systems/PhysicsSystem.hpp"
#include "ECS/Systems/PlayerControlSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Systems/ScriptSystem.hpp"
#include "ECS/Systems/SoundSystem.hpp"
#include "ECS/Systems/PostProcessSystem.hpp"

#include "Inputs/InputHandler.hpp"
#include "Time.hpp"

using namespace BwatEngine;

//initialization
Engine::Engine() : scene(window)
{
    InputHandler::Initialize(GetGLFWwindow());
}

//Main Funtion of engine 
void Engine::Update()
{
    InputHandler::Update();

    float currentFrame = glfwGetTime();
    Time::deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (InputHandler::GetKeyboardDown(KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(GetGLFWwindow(), true);
    }

    scene.playerControlSystem->Update();

    ManageRenderAndPostProcess();

    if (isPlaying)
    {
        scene.physicsSystem->Update();
        scene.soundSystem->Update();
        scene.scriptSystem->Update();
    }




    glfwSwapBuffers(GetGLFWwindow());

}

//Close all content 
void Engine::Close()
{
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
    else if (MainFBO)
        MainFBO->UseAndBind();
    else
        glBindFramebuffer(GL_FRAMEBUFFER, 0); //TODO: Proper handling of default framebuffer

    scene.renderSystem->Update(GetWindow());

    if (isPostProcess)
    {
        // Post Process ... 
        MainFBO->UseAndBind();
        scene.postProcessSystem->Update(scene.renderSystem->GetRenderTextureID(), POSTPROCESS_SHADER::INVERSION);
    }

    MainFBO->Unbind();
}