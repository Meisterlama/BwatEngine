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
    float currentFrame = glfwGetTime();
    Time::deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    InputHandler::Update();

    if (InputHandler::GetKeyboardDown(KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(GetGLFWwindow(), true);
    }

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

    scene.playerControlSystem->Update();

    RenderScene();

    if (updateAudio)
    {
        scene.soundSystem->Update();
    }

    static bool updateScript = false;
    if (InputHandler::GetKeyboardDown(KEY_F4))
    {
        LogInfo("Toggle Script");
        updateScript = !updateScript;

    }
    if (updateScript)
    {
        scene.scriptSystem->Update();
    }

    glfwSwapBuffers(GetWindow().handler);
}

//Close all content 
void Engine::Close()
{
    GetWindow().Close();
}

Engine::~Engine()
{

}

void Engine::RenderScene()
{
    scene.renderSystem->UpdateShadow();

    GLint targetFramebuffer;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &targetFramebuffer);

    bool isPostProcess = false;

    if (isPostProcess)
        scene.postProcessSystem->Begin();

    scene.renderSystem->Update(GetWindow().GetWidth(), GetWindow().GetHeight());

    if (isPostProcess)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, targetFramebuffer);
        scene.postProcessSystem->Apply();
    }

    glDisable(GL_FRAMEBUFFER_SRGB);
}