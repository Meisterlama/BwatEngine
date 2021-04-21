#ifndef ENGINE_ECS_SYSTEMS_RENDER_HPP
#define ENGINE_ECS_SYSTEMS_RENDER_HPP

#include "Math/Vector/Vector3.hpp"

#include "ECS/System.hpp"
#include "ECS/ECS.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/FrameBuffer.hpp"
#include "Window.hpp"
#include "Rendering/CubeMap.hpp"
#include "Rendering/PostProcess.hpp"

namespace BwatEngine
{
    class RenderSystem : public System
    {
        Rendering::FrameBufferObject mainRenderFBO;
        Rendering::Shader shader;
        Rendering::Shader skyboxShader;
        Rendering::CubeMap cubeMap;

        Rendering::PostProcess postProcess;
        Window* window = nullptr;
        EntityID camera = 0;

    public:

        Math::Vec3f clearColor = { 0.5f, 0.5f, 0.5f };

        void Init(Window& win);
        void SetCamera(EntityID _camera);
        void Update(Window& win,Rendering::FrameBufferObject* fbo);
        void ManageCubeMap();
        void ManageEntitiesAndLights();
        void CheckCameraValid();
        void OptionAndClear(Window& win);
        

    };
}

#endif //ENGINE_ECS_SYSTEMS_RENDER_HPP
