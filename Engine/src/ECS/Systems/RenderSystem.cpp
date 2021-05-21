#include "ECS/Coordinator.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/LightComponent.hpp"

#include "Rendering/Light.hpp"
#include "Scene.hpp"

using namespace BwatEngine;

RenderSystem::RenderSystem(int width, int height) : displayWidth(width), displayHeight(height)
{
    shader = { "Assets/Shaders/colors.vs", "Assets/Shaders/multilight.fs" };

    cubeMap.faces = {
        "Assets/cubemap/left.png",
        "Assets/cubemap/right.png",
        "Assets/cubemap/up.png",
        "Assets/cubemap/down.png",
        "Assets/cubemap/front.png",
        "Assets/cubemap/back.png",
    };

    cubeMap.LoadCubeMap();

    shader.Use();
    shader.SetInt("skybox", 0);
    signature.set(Coordinator::GetInstance().GetComponentType<CameraComponent>());
}

void RenderSystem::SetCamera(EntityID _camera)
{
    camera = _camera;
}

// ===================================== MAIN RENDERER ===================================== //


void RenderSystem::Update()
{
    CheckCameraValid();
    OptionAndClear(displayWidth, displayHeight);

    if (camera == 0 )
        return;

    RenderCubeMap();
    RenderEntitiesAndLights();

}

// Gamma correction go to post process
void RenderSystem::RenderCubeMap()
{

    auto& coordinator = Coordinator::GetInstance();

    auto& cameraTransform = coordinator.GetComponent<TransformComponent>(camera);
    auto& cameraComponent = coordinator.GetComponent<CameraComponent>(camera);

    glDepthMask(GL_FALSE);
    cubeMap.shader.Use();
    cubeMap.shader.SetMat4("view", Math::Mat4f::CreateTRSMat(Math::Vec3f(0, 0, 0), cameraTransform.rotation, cameraTransform.scale).Invert());
    cubeMap.shader.SetMat4("projection", cameraComponent.GetProjectionMatrix());
    glBindVertexArray(cubeMap.skyboxVAO);

    if (cubeMap.isDds)
        cubeMap.BindAndDrawCubeMaDdsp();
    else
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap.id);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glDepthMask(GL_TRUE);

}

void RenderSystem::RenderEntitiesAndLights()
{
    auto& coordinator = Coordinator::GetInstance();

    auto& cameraTransform = coordinator.GetComponent<TransformComponent>(camera);
    auto& cameraComponent = coordinator.GetComponent<CameraComponent>(camera);

    Signature signature;
    signature.set(coordinator.GetComponentType<LightComponent>());
    auto lights = coordinator.GetEntitiesWithSignature(signature);

    shader.Use();
    shader.SetMat4("view", Math::Mat4f::CreateTRSMat(cameraTransform.position, cameraTransform.rotation, cameraTransform.scale).Invert());
    shader.SetVec3("viewPos", cameraTransform.position.X, cameraTransform.position.Y, cameraTransform.position.Z);
    shader.SetMat4("proj", cameraComponent.GetProjectionMatrix());
    shader.SetInt("nbrlights", (int)lights.size());

    shader.SetTexture("shadowMap", 10 , shadowMap.depthMap);
    shader.SetMat4("lightSpaceMatrix", lightSpaceMatrix);
    
    shader.SetTextureCubemap("envMap", 20, cubeMap.id);
    
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        std::string index = std::to_string(i);
        auto& light = coordinator.GetComponent<LightComponent>(lights[i]);
        light.ApplyOnShader(&shader, index);
    }
    
    for (auto entity : entities)
    {
        auto& renderableComponent = coordinator.GetComponent<RenderableComponent>(entity);

        if (renderableComponent.model == nullptr)
            continue;

        auto& entityTransform = coordinator.GetComponent<TransformComponent>(entity);
        shader.SetMat4("model", Math::Mat4f::CreateTRSMat(entityTransform.position, entityTransform.rotation, entityTransform.scale));

        if( renderableComponent.materials.size() > 0)
            renderableComponent.materials[0]->ApplyToShader(shader);
        
        renderableComponent.model->Draw(&renderableComponent.materials);
    }
}

void RenderSystem::CheckCameraValid()
{
    auto& coordinator = Coordinator::GetInstance();

    if (!coordinator.IsValid(camera) || coordinator.GetEntitySignature(camera) != signature)
    {
        auto cameras = coordinator.GetEntitiesWithSignature(signature);
        camera = (!cameras.empty()) ? cameras[0] : 0;
    }
}

void RenderSystem::OptionAndClear(int displayWidth, int displayHeight)
{

    glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, displayWidth, displayHeight);
    glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// ===================================== SHADOW ===================================== //


void RenderSystem::UpdateShadow()
{

    CheckCameraValid();

    glCullFace(GL_FRONT);

    GLint previousFramebuffer;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &previousFramebuffer);

    glViewport(0, 0, shadowMap.width, shadowMap.height);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMap.depthMapFbo);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Math::Mat4f lightProjection, lightView;
    float near_plane = -100.f, far_plane = 1000.f;
    lightProjection = Math::Mat4f::CreateOrtho(-300.0f, 300.0f, -300.0f, 300.0f, near_plane, far_plane);

    auto& coordinator = Coordinator::GetInstance();

    Signature signature;
    signature.set(coordinator.GetComponentType<LightComponent>());
    auto lights = coordinator.GetEntitiesWithSignature(signature);

    auto& cameraTransform = coordinator.GetComponent<TransformComponent>(camera);

    // Generate shadoz of the directional light
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        std::string index = std::to_string(i);
        auto& light = coordinator.GetComponent<LightComponent>(lights[i]);

        if (light.typeoflight == Rendering::TYPE_LIGHT::Directional)
        {
            Math::Quatf lightiew = Math::Quatf::LookAt(light.position + light.direction.SafeNormalize() , light.position  , {0, 1, 0 });
            lightView = Math::Mat4f::CreateTRSMat(cameraTransform.position, lightiew, {1});
            lightSpaceMatrix = lightProjection * lightView.GetInverted();
        }
    }

    shadowMap.shader.Use();
    shadowMap.shader.SetMat4("lightSpaceMatrix", lightSpaceMatrix);
    


    // draw all model in deph test 
    for (auto entity : entities)
    {
        auto& renderableComponent = coordinator.GetComponent<RenderableComponent>(entity);

        if (renderableComponent.model == nullptr || !renderableComponent.castShadow)
            continue;

        auto& entityTransform = coordinator.GetComponent<TransformComponent>(entity);

        shadowMap.shader.SetMat4("model", Math::Mat4f::CreateTRSMat(entityTransform.position, entityTransform.rotation, entityTransform.scale));
        renderableComponent.model->Draw(&renderableComponent.materials);
    }

    glCullFace(GL_BACK);
    glBindFramebuffer(GL_FRAMEBUFFER, previousFramebuffer);

}