#ifndef ENGINE_ECS_SYSTEMS_RENDER_HPP
#define ENGINE_ECS_SYSTEMS_RENDER_HPP

#include "Math/Vector/Vector3.hpp"

#include "ECS/System.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/Model.hpp"
#include "Window.hpp"
#include "World.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"

namespace BwatEngine
{
    extern Entity gCamera;

    class RenderSystem : public System
    {
        Rendering::Shader shader;
        Window* window;
        Entity camera = -1;


    public:
        Math::Vec3f clearColor = { 0.5f, 0.5f, 0.5f };

        void Init(Window* _window)
        {
            window = _window;
            shader = {"Assets/basic.vs", "Assets/multilight.fs"};
            Rendering::Light mylight(Rendering::TYPE_LIGHT::Directional, { 0.1f,0.1f,0.5f }, { 0.1f,0.1f,0.5f }, { 0.1f,0.1f,0.5f });
            World::AddLight(mylight);
        }

        void SetCamera(Entity _camera)
        {
            camera = _camera;
        }

        void Update(float dt)
        {
            if (camera == -1)
                return;

            glEnable(GL_DEPTH_TEST);
            glViewport(0, 0, window->GetWidth(), window->GetHeight());
            glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            auto coordinator = Coordinator::GetInstance();

            auto& cameraTransform = coordinator->GetComponent<TransformComponent>(camera).transform;
            auto& cameraProjection = coordinator->GetComponent<CameraComponent>(camera).projectionMat;

            shader.use();
            shader.setMat4("view", cameraTransform.GetTRS().Invert());
            shader.setMat4("proj", cameraProjection);

            shader.setInt("nbrlights", (int)World::GetWorldLights().size());
            for (unsigned int i = 0; i < World::GetWorldLights().size(); i++)
            {
                std::string index = std::to_string(i);
                World::GetWorldLights()[i].ApplyOnShader(&shader, index);
            }
            for (auto entityID : entities)
            {
                auto entityTransform = coordinator->GetComponent<TransformComponent>(entityID).transform;
                auto renderableComponent = coordinator->GetComponent<RenderableComponent>(entityID);
                shader.setMat4("model", entityTransform.GetTRS());

                renderableComponent.model->Draw(shader);
            }

        }
    };
}

#endif //ENGINE_ECS_SYSTEMS_RENDER_HPP