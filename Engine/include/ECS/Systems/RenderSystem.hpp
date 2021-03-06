#ifndef ENGINE_ECS_SYSTEMS_RENDER_HPP
#define ENGINE_ECS_SYSTEMS_RENDER_HPP

#include "Math/Vector/Vector3.hpp"

#include "ECS/System.hpp"
#include "ECS/ECS.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/FrameBuffer.hpp"
#include "Window.hpp"
#include "Rendering/CubeMap.hpp"
#include "Rendering/PostProcess.hpp"
#include "Rendering/ShadowMapping.hpp"
#include "Rendering/Animator.hpp"

namespace BwatEngine
{
    struct ShadowValues
    {
        float intensity = 15.f;
    };

    class RenderSystem : public System
    {
        Rendering::Shader shader;
        Rendering::ShadowMapping shadowMap;

        EntityID cameraID = 0;
        Signature signature;

    public:

        int displayWidth;
        int displayHeight;

        float renderDistance = 1000.f;

        Rendering::CubeMap cubeMap;
        ShadowValues shadowValues;
        
        Math::Vec3f clearColor = { 0.0f, 0.0f, 0.0f };
        Math::Mat4f  lightSpaceMatrix;

        RenderSystem(int Width, int Height);
        void SetCamera(EntityID _camera);
        EntityID GetCameraID();
        virtual void Update() override;
        void RenderWithCamera(CameraComponent cameraComp, TransformComponent cameraTrans);
        void UpdateShadow();
        void RenderCubeMap(const CameraComponent& camera, const TransformComponent& cameraTransform);
        void RenderEntitiesAndLights(const CameraComponent& camera, const TransformComponent& cameraTransform);
        void CheckCameraValid();
        void OptionAndClear(int displayWidth, int displayHeight);

        GLuint GetMainShader() const { return shader.ID; }

      
    };
}

#endif //ENGINE_ECS_SYSTEMS_RENDER_HPP
