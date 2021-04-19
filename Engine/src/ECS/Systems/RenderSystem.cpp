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
    skyboxShader = { "Assets/cubeMap.vs", "Assets/cubeMap.fs" };

    cubeMap.faces = {
        "Assets/cubemap/right.jpg",
        "Assets/cubemap/left.jpg",
        "Assets/cubemap/top.jpg",
        "Assets/cubemap/bottom.jpg",
        "Assets/cubemap/front.jpg",
        "Assets/cubemap/back.jpg",
    };

    cubeMap.LoadCubeMap();
    Rendering::Light mylight(Rendering::TYPE_LIGHT::Directional, { 0.5f,0.5f,0.5f }, { 0.5f,0.5f,0.5f }, { 0.5f,0.5f,0.5f });
    Scene::AddLight(mylight);
}

void RenderSystem::SetCamera(EntityID _camera)
{
    camera = _camera;
}

void RenderSystem::Update(Window& win)
{
    auto& coordinator = Coordinator::GetInstance();

    if (!coordinator.IsValid(camera))
    {
        Signature signature;
        signature.set(coordinator.GetComponentType<CameraComponent>());
        auto cameras = coordinator.GetEntitiesWithSignature(signature);
        camera = (!cameras.empty()) ? cameras[0] : 0;
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, win.GetWidth(), win.GetHeight());
    glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (camera == 0)
        return;

    auto& cameraTransform = coordinator.GetComponent<TransformComponent>(camera);
    auto& cameraComponent = coordinator.GetComponent<CameraComponent>(camera);

    //glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);
    skyboxShader.use();
    skyboxShader.setMat4("view", Math::Mat4f::CreateTRSMat(Math::Vec3f(0, 0, 0), cameraTransform.rotation, cameraTransform.scale).Invert());
    skyboxShader.setMat4("projection", cameraComponent.GetProjectionMatrix());
    glBindVertexArray(cubeMap.skyboxVAO);
    cubeMap.BindCubeMap();
    glDepthMask(GL_TRUE);
    //glDepthFunc(GL_LESS);

    shader.use();
    shader.setMat4("view", Math::Mat4f::CreateTRSMat(cameraTransform.position, cameraTransform.rotation, cameraTransform.scale).Invert());
    shader.setMat4("proj", cameraComponent.GetProjectionMatrix());
    shader.setInt("nbrlights", (int)Scene::GetLights().size());

    for (unsigned int i = 0; i < Scene::GetLights().size(); i++)
    {
        std::string index = std::to_string(i);
        Scene::GetLights()[i].ApplyOnShader(&shader, index);
    }

    for (auto entity : entities)
    {

        auto& entityTransform = coordinator.GetComponent<TransformComponent>(entity);
        auto& renderableComponent = coordinator.GetComponent<RenderableComponent>(entity);
        shader.setMat4("model", Math::Mat4f::CreateTRSMat(entityTransform.position, entityTransform.rotation, entityTransform.scale));

         if (renderableComponent.model != nullptr)
            renderableComponent.model->Draw(&renderableComponent.materials);
    }


    
}