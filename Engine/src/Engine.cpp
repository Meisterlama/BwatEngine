#include "Engine.hpp"

#include "ECS/Systems/PhysicsSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Systems/ScriptSystem.hpp"
#include "ECS/Systems/SoundSystem.hpp"
#include "ECS/Systems/PostProcessSystem.hpp"
#include "ECS/Systems/RenderUISystem.hpp"

#include "Serialization/Serialization.hpp"

#include "Inputs/InputHandler.hpp"
#include "Time.hpp"


using namespace BwatEngine;

//initialization
Engine::Engine() : scene(window)
{
    InputHandler::Initialize(GetGLFWwindow());
    LoadConfig();
}

//Main Funtion of engine 
void Engine::Update()
{
    Time::Update();

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


    renderSystem->Update();

    if (postProcessSystem->isPostProcess)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, targetFramebuffer);
        postProcessSystem->Apply();
    }

    glDisable(GL_FRAMEBUFFER_SRGB);

    renderUISystem->Update();

    glfwSwapBuffers(GetWindow().handler);
}
void Engine::LoadConfig()
{
    using json = nlohmann::json;

    std::ifstream file("Engine.conf");

    if (!file)
        return;

    json js;
    file >> js;

#ifndef BWATEDITOR
    if (js.contains("MainLevel"))
        Serialization::LoadScene(js["MainLevel"]);
#endif
}

Engine::~Engine()
{
    Coordinator::GetInstance().ClearInstance();
}

