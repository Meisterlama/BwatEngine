#include "ECS/Systems/PhysicsSystem.hpp"
#include "Time.hpp"
#include "Physic/PhysicCast.hpp"
#include "ECS/Components/ColliderComponent.hpp"
#include "ECS/Coordinator.hpp"

using namespace BwatEngine;

void PhysicsSystem::Init(Scene* scene, const Math::Vec3f& gravity)  
{
    ptrScene = scene;

    physx::PxSceneDesc SceneDesc(ptrScene->physic.GetPhysics()->getTolerancesScale());
    SceneDesc.gravity = ToPxVec3(gravity);
    SceneDesc.cpuDispatcher = ptrScene->physic.GetCPUDispatcher();
    SceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

    ptrScene->scenePhysic = (ptrScene->physic.GetPhysics()->createScene(SceneDesc));
}

void PhysicsSystem::Update()
{
    for (auto entity : entities)
    {
        auto& rigidBody = Coordinator::GetInstance()->GetComponent<RigidBodyComponent>(entity).rigidBody;
        auto& transform = Coordinator::GetInstance()->GetComponent<TransformComponent>(entity).transform;
        auto& collider = Coordinator::GetInstance()->GetComponent<ColliderComponent>(entity).collider;

        if (rigidBody.ShouldRegister())
        {
            if(!collider)
            {
                BoxCollider* boxCollider = new BoxCollider{ 1 };
                collider = boxCollider;
            }

            rigidBody.AttachCollider(*collider);
            rigidBody.AddActor(ptrScene->scenePhysic);
        }

        if (rigidBody.CompareOldTransform(transform))
        {
            transform.position = rigidBody.GetPosition();
            transform.rotation = rigidBody.GetRotation();
        }
        else
        {
            rigidBody.SetTransform(transform);
        }
    }

    ptrScene->scenePhysic->simulate(Time::deltaTime);
    ptrScene->scenePhysic->fetchResults(true);
};