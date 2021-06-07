#include "ECS/Coordinator.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/AnimatorComponent.hpp"
#include "ECS/Components/LightComponent.hpp"

#include "Time.hpp"
#include "Rendering/Light.hpp"
#include "Rendering/Primitives.hpp"
#include "Scene.hpp"

using namespace BwatEngine;

RenderSystem::RenderSystem(int width, int height) : displayWidth(width), displayHeight(height)
{
    shader = { "EngineAssets/Shaders/colors.vs", "EngineAssets/Shaders/multilight.fs" };

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
    signature.set(Coordinator::GetInstance().GetComponentType<TransformComponent>());
}

void RenderSystem::SetCamera(EntityID _camera)
{
    cameraID = _camera;
}

EntityID RenderSystem::GetCameraID()
{
    CheckCameraValid();
    return cameraID;
}

// ===================================== MAIN RENDERER ===================================== //


void RenderSystem::Update()
{

    CheckCameraValid();
    OptionAndClear(displayWidth, displayHeight);

    if (cameraID == 0)
        return;
    auto& coordinator = Coordinator::GetInstance();
    auto& cameraTransform = coordinator.GetComponent<TransformComponent>(cameraID);
    auto& camera = coordinator.GetComponent<CameraComponent>(cameraID);

    RenderCubeMap(camera, cameraTransform);
    RenderEntitiesAndLights(camera, cameraTransform);
}

// Gamma correction go to post process
void RenderSystem::RenderCubeMap(const CameraComponent& camera, const TransformComponent& cameraTransform)
{
    glDepthMask(GL_FALSE);

    cubeMap.shader.Use();
    cubeMap.shader.SetMat4("view", Math::Mat4f::CreateTRSMat(Math::Vec3f(0, 0, 0), cameraTransform.rotation, cameraTransform.scale).Invert());
    cubeMap.shader.SetMat4("projection", camera.GetProjectionMatrix());
    glBindVertexArray(cubeMap.skyboxVAO);

    if (cubeMap.isDds)
        cubeMap.BindAndDrawCubeMaDdsp();
    else
    {
        cubeMap.BindCubeMap();
        //glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap.id);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glDepthMask(GL_TRUE);
}

void RenderSystem::RenderEntitiesAndLights(const CameraComponent& camera, const TransformComponent& cameraTransform)
{
    auto& coordinator = Coordinator::GetInstance();

    Signature signature;
    signature.set(coordinator.GetComponentType<LightComponent>());
    auto lights = coordinator.GetEntitiesWithSignature(signature);

    shader.Use();
    shader.SetMat4("view", Math::Mat4f::CreateTRSMat(cameraTransform.position, cameraTransform.rotation, cameraTransform.scale).Invert());
    shader.SetVec3("viewPos", cameraTransform.position.X, cameraTransform.position.Y, cameraTransform.position.Z);
    shader.SetMat4("proj", camera.GetProjectionMatrix());
    shader.SetInt("nbrlights", (int)lights.size());

    shader.SetTexture("shadowMap", 10 , shadowMap.depthMap);
    shader.SetMat4("lightSpaceMatrix", lightSpaceMatrix);
    
    shader.SetTextureCubemap("envMap", 20, cubeMap.id);

    shader.SetFloat("intensity", shadowValues.intensity);
    
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        std::string index = std::to_string(i);
        auto& light = coordinator.GetComponent<LightComponent>(lights[i]);
        
        if (coordinator.HaveComponent<TransformComponent>(lights[i]))
        {
            auto& transform = coordinator.GetComponent<TransformComponent>(lights[i]);
            light.position = transform.position ;
            light.direction = transform.rotation.Rotate({ 0,0,1 });
        }

        light.ApplyOnShader(&shader, index);
    }
    
    for (auto entity : entities)
    {
        if (coordinator.HaveComponent<AnimatorComponent>(entity))
        {
            shader.SetBool("skinned", true);
            auto& animComponent = coordinator.GetComponent< AnimatorComponent>(entity);
            auto transforms = animComponent.animator.GetFinalBoneMatrices();
            for (int i = 0; i < transforms.size(); ++i)
                shader.SetMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
            
        }
        else
            shader.SetBool("skinned", false);

        auto& renderableComponent = coordinator.GetComponent<RenderableComponent>(entity);

        if (renderableComponent.model == nullptr)
            continue;

        auto& entityTransform = coordinator.GetComponent<TransformComponent>(entity);
        shader.SetMat4("model", Math::Mat4f::CreateTRSMat(entityTransform.position, entityTransform.rotation, entityTransform.scale));

        if( renderableComponent.materials.size() > 0)
            renderableComponent.materials[0]->ApplyToShader(shader);
        
        renderableComponent.model->Draw(shader ,&renderableComponent.materials);
    }
    
}

void RenderSystem::CheckCameraValid()
{
    auto& coordinator = Coordinator::GetInstance();

    if (!coordinator.IsValid(cameraID) || coordinator.GetEntitySignature(cameraID) != signature)
    {
        auto cameras = coordinator.GetEntitiesWithSignature(signature);
        cameraID = (!cameras.empty()) ? cameras[0] : 0;
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

    if (cameraID == 0)
        return;


    auto& coordinator = Coordinator::GetInstance();
    auto& cameraTransform = coordinator.GetComponent<TransformComponent>(cameraID);


    GLint previousFramebuffer;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &previousFramebuffer);

    glViewport(0, 0, shadowMap.width, shadowMap.height);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMap.depthMapFbo);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_FRONT);
  
    Math::Mat4f lightProjection, lightView;
    float near_plane = -100.f, far_plane = 1000.f;
    lightProjection = Math::Mat4f::CreateOrtho(-200.0f, 200.0f, -200.0f, 200.0f, near_plane, far_plane);

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
        if (coordinator.HaveComponent<AnimatorComponent>(entity))
        {
            shadowMap.shader.SetBool("skinned", true);
            auto& animComponent = coordinator.GetComponent< AnimatorComponent>(entity);
            auto transforms = animComponent.animator.GetFinalBoneMatrices();
            for (int i = 0; i < transforms.size(); ++i)
                shadowMap.shader.SetMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

        }
        else
            shadowMap.shader.SetBool("skinned", false);

        auto& renderableComponent = coordinator.GetComponent<RenderableComponent>(entity);

        if (renderableComponent.model == nullptr || !renderableComponent.castShadow)
            continue;

        auto& entityTransform = coordinator.GetComponent<TransformComponent>(entity);

        shadowMap.shader.SetMat4("model", Math::Mat4f::CreateTRSMat(entityTransform.position, entityTransform.rotation, entityTransform.scale));
        renderableComponent.model->Draw(shadowMap.shader,&renderableComponent.materials);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, previousFramebuffer);


    glCullFace(GL_BACK);

}

void RenderSystem::RenderWithCamera(CameraComponent camera, TransformComponent cameraTransform)
{
    OptionAndClear(displayWidth, displayHeight);
    glDisable(GL_FRAMEBUFFER_SRGB);
    RenderCubeMap(camera, cameraTransform);
    RenderEntitiesAndLights(camera, cameraTransform);
}
