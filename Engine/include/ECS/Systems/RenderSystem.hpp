#ifndef ENGINE_ECS_SYSTEMS_RENDER_HPP
#define ENGINE_ECS_SYSTEMS_RENDER_HPP

#include "Math/Vector/Vector3.hpp"

#include "ECS/System.hpp"
#include "ECS/ECS.hpp"
#include "Rendering/Shader.hpp"
#include "Window.hpp"
#include "Rendering/CubeMap.hpp"

namespace BwatEngine
{
    class RenderSystem : public System
    {

        Rendering::Shader shader;
        Rendering::Shader skyboxShader;
        Rendering::CubeMap cubeMap;

        Window* window = nullptr;
        EntityID camera = 0;

    public:

        Math::Vec3f clearColor = { 0.5f, 0.5f, 0.5f };

        void Init();
        void SetCamera(EntityID _camera);
        void Update(Window& win);
        

    };
}

#endif //ENGINE_ECS_SYSTEMS_RENDER_HPP
