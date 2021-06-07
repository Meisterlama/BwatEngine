#include "ECS/Systems/RenderUISystem.hpp"
#include "ECS/Coordinator.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "ECS/Components/Image2DComponent.hpp"


using namespace BwatEngine;

RenderUISystem::RenderUISystem() : shader("EngineAssets/Shaders/UIRender.vs", "EngineAssets/Shaders/UIRender.fs")
{
    view = Math::Mat4f(1.0f);
    proj = Math::Mat4f::CreateOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);
}

void RenderUISystem::Update()
{
    glDisable(GL_DEPTH_TEST);

    auto& coordinator = Coordinator::GetInstance();
    shader.Use();
    shader.SetMat4("view", view);
    shader.SetMat4("projection", proj);

    for (auto entity : entities)
    {
        auto& image = coordinator.GetComponent<Image2DComponent>(entity);
        if (!image.isActive || !image.texture)
            break;
        Math::Mat4f model = Math::Mat4f::CreateTRSMat(Math::Vec3f {image.position.X / 100.f, image.position.Y / 100.f, -0.1f},
                                          Math::Vec3f{0.f, 0.f, Math::ToRads(image.rotation)},
                                          Math::Vec3f{image.scale.X / 100.f, image.scale.Y / 100.f, 1.f}
        );

        shader.SetMat4("model", model);
        image.Use();
        usedQuad.Draw();
    }
    glEnable(GL_DEPTH_TEST);
}
