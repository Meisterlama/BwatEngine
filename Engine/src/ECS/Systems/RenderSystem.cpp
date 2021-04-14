#include "ECS/Coordinator.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"

#include "Rendering/Light.hpp"
#include "Scene.hpp"

using namespace BwatEngine;

void RenderSystem::Init()
{
    shader = { "Assets/colors.vs", "Assets/colors.fs" };
    Rendering::Light mylight(Rendering::TYPE_LIGHT::Directional, { 0.5f,0.5f,0.5f }, { 0.5f,0.5f,0.5f }, { 0.5f,0.5f,0.5f });
    Scene::AddLight(mylight);
}

void RenderSystem::SetCamera(EntityID _camera)
{
    camera = _camera;
}

void RenderSystem::Update(Window& win)
{
    if (camera == 0)
        return;

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, win.GetWidth(), win.GetHeight());
    glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto& coordinator = Coordinator::GetInstance();

    auto& cameraTransform = coordinator.GetComponent<TransformComponent>(camera);
    auto& cameraProjection = coordinator.GetComponent<CameraComponent>(camera).projectionMat;

    shader.use();
    shader.setMat4("view", Math::Mat4f::CreateTRSMat(cameraTransform.position, cameraTransform.rotation, cameraTransform.scale).Invert());
    shader.setMat4("proj", cameraProjection);
    shader.setInt("nbrlights", (int)Scene::GetLights().size());

    for (unsigned int i = 0; i < Scene::GetLights().size(); i++)
    {
        std::string index = std::to_string(i);
        Scene::GetLights()[i].ApplyOnShader(&shader, index);
    }

    for (auto entity : entities)
    {
        auto entityTransform = coordinator.GetComponent<TransformComponent>(entity);
        auto renderableComponent = coordinator.GetComponent<RenderableComponent>(entity);
         shader.setMat4("model", Math::Mat4f::CreateTRSMat(entityTransform.position, entityTransform.rotation, entityTransform.scale));

        renderableComponent.model->Draw(&renderableComponent.materials);
    }

}