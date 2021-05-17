#include "ECS/Coordinator.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/LightComponent.hpp"

#include "Rendering/Light.hpp"
#include "Scene.hpp"

using namespace BwatEngine;

RenderSystem::RenderSystem()
{
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

    shader.Use();
    shader.SetInt("skybox", 0);
    signature.set(Coordinator::GetInstance().GetComponentType<CameraComponent>());
}

void RenderSystem::SetCamera(EntityID _camera)
{
    camera = _camera;
}

// ===================================== MAIN RENDERER ===================================== //


void RenderSystem::Update(int displayWidth, int displayHeight)
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

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap.id);
    glDrawArrays(GL_TRIANGLES, 0, 36);

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
        auto& entityTransform = coordinator.GetComponent<TransformComponent>(entity);
        auto& renderableComponent = coordinator.GetComponent<RenderableComponent>(entity);
        shader.SetMat4("model", Math::Mat4f::CreateTRSMat(entityTransform.position, entityTransform.rotation, entityTransform.scale));

        if (renderableComponent.materials.size() > 0)
        {
            Rendering::Material& mat = *renderableComponent.materials[0];

            shader.SetFloat("material.shininess", mat.shininess);
            shader.SetBool("material.isColor", mat.isColor);
            shader.SetVec4("material.color", mat.color.X, mat.color.Y, mat.color.Z, mat.color.W);


            if (mat.diffuse != nullptr)

                shader.SetInt("material.diffuse", 0);
            if (mat.specular != nullptr)
                shader.SetInt("material.specular", 1);
            if (mat.normal != nullptr)
            {
                shader.SetInt("material.normal", 2);
                shader.SetInt("material.isNormal", 1);
            }
            else
                shader.SetInt("material.isNormal", 0);
        }

        if (renderableComponent.model != nullptr)
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
    GLint previousFramebuffer;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &previousFramebuffer);

    glViewport(0, 0, shadowMap.width, shadowMap.height);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMap.depthMapFbo);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Math::Mat4f lightProjection, lightView;
    float near_plane = 0.0f, far_plane = 1000.f;
    lightProjection = Math::Mat4f::CreateOrtho(-150.0f, 150.0f, -150.0f, 150.0f, near_plane, far_plane);

    auto& coordinator = Coordinator::GetInstance();

    Signature signature;
    signature.set(coordinator.GetComponentType<LightComponent>());
    auto lights = coordinator.GetEntitiesWithSignature(signature);

    // Generate shadoz of the directional light
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        std::string index = std::to_string(i);
        auto& light = coordinator.GetComponent<LightComponent>(lights[i]);
        if (light.typeoflight == Rendering::TYPE_LIGHT::Directional)
        {
            lightView = Math::Mat4f::CreateTRSMat(light.position, Math::Vec3f{ Math::ToRads(light.direction.Y * 90),-Math::ToRads(light.direction.X * 90),Math::ToRads(light.direction.Z * 90) }, { 1 }).GetInverted();
            lightSpaceMatrix = lightProjection * lightView;
        }
    }

    shadowMap.shader.Use();
    shadowMap.shader.SetMat4("lightSpaceMatrix", lightSpaceMatrix);
    
    // draw all model in deph test 
    for (auto entity : entities)
    {
        auto& entityTransform = coordinator.GetComponent<TransformComponent>(entity);
        auto& renderableComponent = coordinator.GetComponent<RenderableComponent>(entity);
        shadowMap.shader.SetMat4("model", Math::Mat4f::CreateTRSMat(entityTransform.position, entityTransform.rotation, entityTransform.scale));

        if (renderableComponent.model != nullptr)
            renderableComponent.model->Draw(&renderableComponent.materials);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, previousFramebuffer);

}