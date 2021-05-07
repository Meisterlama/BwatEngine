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

// ===================================== MAIN RENDERER ===================================== //


void RenderSystem::Update(Window& win)
{
    CheckCameraValid();
    OptionAndClear(win);

    if (camera == 0)
        return;
    
    ManageCubeMap();
    ManageEntitiesAndLights();

}

// Gamma correction go to post process
void RenderSystem::ManageCubeMap()
{

    auto& coordinator = Coordinator::GetInstance();

    auto& cameraTransform = coordinator.GetComponent<TransformComponent>(camera);
    auto& cameraComponent = coordinator.GetComponent<CameraComponent>(camera);

    glDepthMask(GL_FALSE);
    cubeMap.shader.use();
    cubeMap.shader.setMat4("view", Math::Mat4f::CreateTRSMat(Math::Vec3f(0, 0, 0), cameraTransform.rotation, cameraTransform.scale).Invert());
    cubeMap.shader.setMat4("projection", cameraComponent.GetProjectionMatrix());
    cubeMap.shader.setFloat("gamma", cameraComponent.gamma);
    cubeMap.shader.setBool("isGamma", cameraComponent.isGamma);
    glBindVertexArray(cubeMap.skyboxVAO);

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap.id);
    glDrawArrays(GL_TRIANGLES, 0, 36);

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

    shader.SetTexture("shadowMap", 10 , shadowMap.depthMap);
    shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
    
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
        shader.setMat4("model", Math::Mat4f::CreateTRSMat(entityTransform.position, entityTransform.rotation, entityTransform.scale));

        if (renderableComponent.materials.size() > 0)
        {
            shader.setFloat("material.shininess", renderableComponent.materials[0]->shininess);

            if (renderableComponent.materials[0]->diffuse != nullptr)
                shader.setInt("material.diffuse", 0);
            if (renderableComponent.materials[0]->specular != nullptr)
                shader.setInt("material.specular", 1);
            if (renderableComponent.materials[0]->normal != nullptr)
            {
                shader.setInt("material.normal", 2);
                shader.setInt("material.isNormal", 1);
            }
            else
                shader.setInt("material.isNormal", 0);
        }

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

// ===================================== SHADOW ===================================== //


void RenderSystem::UpdateShadow()
{
    glViewport(0, 0, shadowMap.width, shadowMap.height);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMap.depthMapFbo);
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

    shadowMap.shader.use();
    shadowMap.shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
    
    // draw all model in deph test 
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