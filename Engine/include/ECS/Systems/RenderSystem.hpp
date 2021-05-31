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
    class RenderSystem : public System
    {
        Rendering::Shader shader;

        Rendering::CubeMap cubeMap;
        Rendering::ShadowMapping shadowMap;

        EntityID cameraID = 0;
        Signature signature;

    public:

        int displayWidth;
        int displayHeight;

        Math::Vec3f clearColor = { 0.0f, 0.0f, 0.0f };
        Math::Mat4f  lightSpaceMatrix;

        RenderSystem(int Width, int Height);
        void SetCamera(EntityID _camera);
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
