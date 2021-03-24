#ifndef ENGINE_ECS_SYSTEMS_RENDER_HPP
#define ENGINE_ECS_SYSTEMS_RENDER_HPP

#include "Math/Vector/Vector3.hpp"

#include "ECS/System.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/Model.hpp"
#include "Window.hpp"
#include "Scene.hpp"

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

        void Init();
        void SetCamera(Entity _camera);
        void Update(Window& win);

        
    };
}

#endif //ENGINE_ECS_SYSTEMS_RENDER_HPP
