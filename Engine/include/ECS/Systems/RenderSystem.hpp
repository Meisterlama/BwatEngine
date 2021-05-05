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
#include "Rendering/ShadowMapping.hpp"

namespace BwatEngine
{
    class RenderSystem : public System
    {
        Rendering::FrameBufferObject mainRenderFBO;
        Rendering::Shader shader;

        Rendering::CubeMap cubeMap;
        Rendering::ShadowMapping shadowMap;

        Window* window = nullptr;
        EntityID camera = 0;

    public:

        Math::Vec3f clearColor = { 0.5f, 0.5f, 0.5f };
        Math::Mat4f  lightSpaceMatrix;

        void Init(Window& win);
        void SetCamera(EntityID _camera);
        void Update(Window& win);
        void UpdateShadow();
        void ManageCubeMap();
        void ManageEntitiesAndLights();
        void CheckCameraValid();
        void OptionAndClear(Window& win);

        GLuint GetRenderTextureID() { return mainRenderFBO.textureColor.id; }
        void BindMainRenderFBO() { mainRenderFBO.UseAndBind(); }

      
    };
}

#endif //ENGINE_ECS_SYSTEMS_RENDER_HPP
