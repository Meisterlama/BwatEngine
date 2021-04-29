#include "ECS/Coordinator.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/LightComponent.hpp"

#include "Rendering/Light.hpp"
#include "Scene.hpp"

using namespace BwatEngine;

void RenderSystem::Init(Window& win)
{
    mainRenderFBO.Rezise(win.GetWidth(),win.GetHeight());
    shader = { "Assets/Shaders/colors.vs", "Assets/Shaders/multilight.fs" };

    cubeMap.faces = {
        "Assets/cubemap/right.jpg",
        "Assets/cubemap/left.jpg",
        "Assets/cubemap/top.jpg",
        "Assets/cubemap/bottom.jpg",
        "Assets/cubemap/front.jpg",
        "Assets/cubemap/back.jpg",
    };

    cubeMap.LoadCubeMap();

    shader.use();
    shader.setInt("skybox", 0);
}

void RenderSystem::SetCamera(EntityID _camera)
{
    camera = _camera;
}

void RenderSystem::UpdateShadow()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Math::Mat4f lightProjection, lightView;

    float near_plane = 1.0f, far_plane = 7.5f;
    
    // Bug : Matrix need to check
    lightProjection = Math::Mat4f::CreateOrtho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    lightView = Math::Mat4f::LookAt(Math::Vec3f(0.0f,1.0f,0.0f), Math::Vec3f(0.0f), Math::Vec3f(0.0, 1.0, 0.0));
    lightSpaceMatrix = lightProjection * lightView;

    shadowMap.shader.use();
    shadowMap.shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

    glViewport(0, 0, shadowMap.width, shadowMap.height);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMap.depthMapFbo);
    glClear(GL_DEPTH_BUFFER_BIT);


    auto& coordinator = Coordinator::GetInstance();

    for (auto entity : entities)
    {
        auto& entityTransform = coordinator.GetComponent<TransformComponent>(entity);
        auto& renderableComponent = coordinator.GetComponent<RenderableComponent>(entity);
        shadowMap.shader.setMat4("model", Math::Mat4f::CreateTRSMat(entityTransform.position, entityTransform.rotation, entityTransform.scale));

        if (renderableComponent.model != nullptr)
            renderableComponent.model->Draw(&renderableComponent.materials);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void RenderSystem::Update(Window& win)
{
    
    CheckCameraValid();
    OptionAndClear(win);

    if (camera == 0)
        return;
    
    ManageCubeMap();
    ManageEntitiesAndLights();

}

void RenderSystem::ManageCubeMap()
{

    auto& coordinator = Coordinator::GetInstance();

    auto& cameraTransform = coordinator.GetComponent<TransformComponent>(camera);
    auto& cameraComponent = coordinator.GetComponent<CameraComponent>(camera);

    glDepthMask(GL_FALSE);
    cubeMap.shader.use();
    cubeMap.shader.setMat4("view", Math::Mat4f::CreateTRSMat(Math::Vec3f(0, 0, 0), cameraTransform.rotation, cameraTransform.scale).Invert());
    cubeMap.shader.setMat4("projection", cameraComponent.GetProjectionMatrix());
    shader.setFloat("gamma", cameraComponent.gamma);
    shader.setBool("isGamma", cameraComponent.isGamma);
    glBindVertexArray(cubeMap.skyboxVAO);
    cubeMap.BindCubeMap();
    glDepthMask(GL_TRUE);

}

void RenderSystem::ManageEntitiesAndLights()
{
    auto& coordinator = Coordinator::GetInstance();

    auto& cameraTransform = coordinator.GetComponent<TransformComponent>(camera);
    auto& cameraComponent = coordinator.GetComponent<CameraComponent>(camera);

    Signature signature;
    signature.set(coordinator.GetComponentType<LightComponent>());
    auto lights = coordinator.GetEntitiesWithSignature(signature);


    shader.use();
    shader.setMat4("view", Math::Mat4f::CreateTRSMat(cameraTransform.position, cameraTransform.rotation, cameraTransform.scale).Invert());
    shader.setVec3("viewPos", cameraTransform.position.X, cameraTransform.position.Y, cameraTransform.position.Z);
    shader.setMat4("proj", cameraComponent.GetProjectionMatrix());
    shader.setInt("nbrlights", (int)lights.size());
    shader.setFloat("gamma", cameraComponent.gamma);
    shader.setBool("isGamma", cameraComponent.isGamma);
    shader.setInt("shadowMap", shadowMap.depthMap);

    // To Do : change for multi lighting
    shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
    
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        std::string index = std::to_string(i);
        auto& light = coordinator.GetComponent<LightComponent>(lights[i]);
        light.ApplyOnShader(&shader, index);

    }

    for (auto entity : entities)
    {

        auto& entityTransform = coordinator.GetComponent<TransformComponent>(entity);
        auto& renderableComponent = coordinator.GetComponent<RenderableComponent>(entity);
        shader.setMat4("model", Math::Mat4f::CreateTRSMat(entityTransform.position, entityTransform.rotation, entityTransform.scale));

        shader.setFloat("material.shininess", renderableComponent.materials[0]->shininess);
        
        //To do ! Why doesn't work need help
        //if (renderableComponent.materials[0]->diffuse != nullptr)
        //    shader.setInt("material.diffuse", renderableComponent.materials[0]->diffuse->id);
        //if (renderableComponent.materials[0]->specular != nullptr)
        //    shader.setInt("material.specular", renderableComponent.materials[0]->specular->id);

        if (renderableComponent.model != nullptr)
            renderableComponent.model->Draw(&renderableComponent.materials);
    }
}

void RenderSystem::CheckCameraValid()
{
    auto& coordinator = Coordinator::GetInstance();

    if (!coordinator.IsValid(camera))
    {
        Signature signature;
        signature.set(coordinator.GetComponentType<CameraComponent>());
        auto cameras = coordinator.GetEntitiesWithSignature(signature);
        camera = (!cameras.empty()) ? cameras[0] : 0;
    }
}

void RenderSystem::OptionAndClear(Window& win)
{

    glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, win.GetWidth(), win.GetHeight());
    glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}