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
        Rendering::Shader shader;

        Rendering::CubeMap cubeMap;
        Rendering::ShadowMapping shadowMap;

        EntityID camera = 0;
        Signature signature;

    public:

        int displayWidth;
        int displayHeight;

        Math::Vec3f clearColor = { 0.5f, 0.5f, 0.5f };
        Math::Mat4f  lightSpaceMatrix;

        RenderSystem(int Width, int Height);
        void SetCamera(EntityID _camera);
        virtual void Update() override;
        void UpdateShadow();
        void RenderCubeMap();
        void RenderEntitiesAndLights();
        void CheckCameraValid();
        void OptionAndClear(int displayWidth, int displayHeight);

        GLuint GetMainShader() const { return shader.ID; }

      
    };
}

#endif //ENGINE_ECS_SYSTEMS_RENDER_HPP
