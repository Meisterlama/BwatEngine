#include "Engine.hpp"

#include "ECS/Systems/PhysicsSystem.hpp"
#include "ECS/Systems/PlayerControlSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Systems/ScriptSystem.hpp"
#include "ECS/Systems/SoundSystem.hpp"
#include "ECS/Systems/PostProcessSystem.hpp"
#include "ECS/Systems/RenderUISystem.hpp"

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

    auto& coordinator = Coordinator::GetInstance();
    auto renderSystem = coordinator.GetSystem<RenderSystem>();
    auto postProcessSystem = coordinator.GetSystem<PostProcessSystem>();
    auto renderUISystem = coordinator.GetSystem<RenderUISystem>();

    renderSystem->displayHeight = GetWindow().GetHeight();
    renderSystem->displayWidth = GetWindow().GetWidth();

    Coordinator::GetInstance().UpdateSystems(isPlaying);

    renderSystem->UpdateShadow();
    GLint targetFramebuffer;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &targetFramebuffer);


    if (postProcessSystem->isPostProcess)
        postProcessSystem->Begin();

    if (renderUISystem->isRenderUI)
        renderUISystem->Begin();

    renderSystem->Update();

    if (postProcessSystem->isPostProcess)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, targetFramebuffer);
        postProcessSystem->Apply();
    }

    if (renderUISystem->isRenderUI)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, targetFramebuffer);
        renderUISystem->Update();
    }



    glDisable(GL_FRAMEBUFFER_SRGB);

    glfwSwapBuffers(GetWindow().handler);
}

Engine::~Engine()
{
    Coordinator::GetInstance().ClearInstance();
    std::remove("temp.txt");
}

