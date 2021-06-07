#include "ECS/Coordinator.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/ColliderComponent.hpp"
#include "ECS/Systems/ColliderDrawSystem.hpp"
#include "Physic/PhysicCast.hpp"

namespace BwatEngine
{
    ColliderDrawSystem::ColliderDrawSystem()
    {
        shader = {"EngineAssets/Shaders/wireframe.vs", "EngineAssets/Shaders/wireframe.fs"};
        signature.set(Coordinator::GetInstance().GetComponentType<CameraComponent>());
        cube = std::move(CreateCube());
        sphere = std::move(CreateSphere(5, 5));
    }

    void ColliderDrawSystem::CheckCameraValid()
    {
        auto &coordinator = Coordinator::GetInstance();

        if (!coordinator.IsValid(cameraID) || coordinator.GetEntitySignature(cameraID) != signature)
        {
            auto cameras = coordinator.GetEntitiesWithSignature(signature);
            cameraID = (!cameras.empty()) ? cameras[0] : 0;
        }
    }

    void ColliderDrawSystem::Update()
    {
        CheckCameraValid();
        if (cameraID == 0)
            return;
        auto &coordinator = Coordinator::GetInstance();
        auto &cameraTransform = coordinator.GetComponent<TransformComponent>(cameraID);
        auto &camera = coordinator.GetComponent<CameraComponent>(cameraID);

        DrawWithCamera(camera, cameraTransform);
    }

    void ColliderDrawSystem::DrawWithCamera(const CameraComponent &camera, const TransformComponent &cameraTransform)
    {
        auto &coordinator = Coordinator::GetInstance();
        shader.Use();
        shader.SetMat4("view", Math::Mat4f::CreateTRSMat(cameraTransform.position, cameraTransform.rotation,
                                                         cameraTransform.scale).Invert());
        shader.SetVec3("viewPos", cameraTransform.position.X, cameraTransform.position.Y, cameraTransform.position.Z);
        shader.SetMat4("proj", camera.GetProjectionMatrix());

        for (auto entity : entities)
        {
            auto &entityTransform = coordinator.GetComponent<TransformComponent>(entity);
            auto& collider = coordinator.GetComponent<ColliderComponent>(entity);
            switch (collider.GetShapeType())
            {
                case Collider::CUBE:
                {
                    physx::PxBoxGeometry boxGeometry;
                    collider.GetShape()->getBoxGeometry(boxGeometry);
                    shader.SetMat4("model", Math::Mat4f::CreateTRSMat(
                            entityTransform.position,
                            entityTransform.rotation,
                            ToBwatVec3(boxGeometry.halfExtents) * 2.0f)
                    );
                    cube.DrawWireFrame();
                    break;
                }
                case Collider::SPHERE:
                {
                    physx::PxSphereGeometry sphereGeometry;
                    collider.GetShape()->getSphereGeometry(sphereGeometry);
                    shader.SetMat4("model", Math::Mat4f::CreateTRSMat(entityTransform.position, entityTransform.rotation,
                                                                      {sphereGeometry.radius}));
                    sphere.DrawWireFrame();
                    break;
                }
            }
        }
    }
}