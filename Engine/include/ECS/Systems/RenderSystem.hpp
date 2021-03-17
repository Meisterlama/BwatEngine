#ifndef ENGINE_ECS_SYSTEMS_RENDER_HPP
#define ENGINE_ECS_SYSTEMS_RENDER_HPP

#include "Math/Vector/Vector3.hpp"

#include "ECS/System.hpp"
#include "ECS/Entity.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/Model.hpp"
#include "Window.hpp"
#include "Scene.hpp"

namespace BwatEngine
{
    extern Entity gCamera;

    class RenderSystem : public System
    {
        Rendering::Shader shader;
        Window* window;
        Entity* camera;


    public:
        Math::Vec3f clearColor = { 0.5f, 0.5f, 0.5f };

        void Init()
        {
            window = &Engine::GetContext().window;
            shader = {"Assets/basic.vs", "Assets/multilight.fs"};
            Rendering::Light mylight(Rendering::TYPE_LIGHT::Directional, { 0.1f,0.1f,0.5f }, { 0.1f,0.1f,0.5f }, { 0.1f,0.1f,0.5f });
            Scene::AddLight(mylight);
        }

        void SetCamera(Entity* _camera)
        {
            camera = _camera;
        }

        void Update()
        {
            if (!camera)
                return;

            glEnable(GL_DEPTH_TEST);
            glViewport(0, 0, window->GetWidth(), window->GetHeight());
            glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            auto& cameraTransform = camera->GetComponent<TransformComponent>().transform;
            auto& cameraProjection = camera->GetComponent<CameraComponent>().projectionMat;

            shader.use();
            shader.setMat4("view", Math::Mat4f::CreateTRSMat(cameraTransform.position, cameraTransform.rotation, cameraTransform.scale).Invert());
            shader.setMat4("proj", cameraProjection);

            shader.setInt("nbrlights", (int)Scene::GetLights().size());
            for (unsigned int i = 0; i < Scene::GetLights().size(); i++)
            {
                std::string index = std::to_string(i);
                Scene::GetLights()[i].ApplyOnShader(&shader, index);
            }
            for (auto entityID : entities)
            {
                Entity entity{entityID};
                auto entityTransform = entity.GetComponent<TransformComponent>().transform;
                auto renderableComponent = entity.GetComponent<RenderableComponent>();
                shader.setMat4("model", Math::Mat4f::CreateTRSMat(entityTransform.position, entityTransform.rotation, entityTransform.scale));

                renderableComponent.model->Draw(shader);
            }

        }
    };
}

#endif //ENGINE_ECS_SYSTEMS_RENDER_HPP