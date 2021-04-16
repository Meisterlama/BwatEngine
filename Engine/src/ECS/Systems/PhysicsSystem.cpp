#include "ECS/Systems/PhysicsSystem.hpp"
#include "Time.hpp"
#include "Physic/PhysicCast.hpp"
#include "ECS/Components/ColliderComponent.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/RigidBodyComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"


using namespace BwatEngine;

void PhysicsSystem::Init(PhysicScene* scene) 
{
    ptrPhysicScene = scene;
}

void PhysicsSystem::Update()
{
    for (auto entity : entities)
    {
        auto& rigidBody = Coordinator::GetInstance().GetComponent<RigidBodyComponent>(entity);
        auto& transform = Coordinator::GetInstance().GetComponent<TransformComponent>(entity);
        auto& collider = Coordinator::GetInstance().GetComponent<ColliderComponent>(entity).collider;

        if (rigidBody->ShouldRegister())
        {
            if(!collider)
            {
                BoxCollider* boxCollider = new BoxCollider{ 1 };
                collider = boxCollider;
            }

            rigidBody->AttachCollider(*collider);
            rigidBody->AddActor(ptrPhysicScene->GetPhysicScene());
        }

        if (rigidBody->CompareOldTransform(transform))
        {
            transform.position = rigidBody->GetPosition();
            transform.rotation = rigidBody->GetRotation();
        }
        else
        {
            rigidBody->SetTransform(transform);
        }
    }

    ptrPhysicScene->GetPhysicScene()->simulate(Time::deltaTime);
    ptrPhysicScene->GetPhysicScene()->fetchResults(true);
};