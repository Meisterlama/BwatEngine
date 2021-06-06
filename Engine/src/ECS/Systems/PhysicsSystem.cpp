#include "ECS/Systems/PhysicsSystem.hpp"
#include "Time.hpp"
#include "ECS/Components/ColliderComponent.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/RigidBodyComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"


using namespace BwatEngine;

void PhysicsSystem::Update()
{
    for (auto entity : entities)
    {
        auto& rigidBody = Coordinator::GetInstance().GetComponent<RigidBodyComponent>(entity);
        auto& transform = Coordinator::GetInstance().GetComponent<TransformComponent>(entity);
        auto& collider = Coordinator::GetInstance().GetComponent<ColliderComponent>(entity);

        if (rigidBody.ShouldRegister())
        {
            rigidBody.AttachCollider(collider);
            rigidBody.AddActor(ptrPhysicScene);
        }

        if (rigidBody.CompareOldPosition(transform.position))
        {
            transform.position = rigidBody.GetPosition();
        }
        else
        {
            rigidBody.SetPosition(transform.position);
        }

        if (rigidBody.CompareOldRotation(transform.rotation))
        {
            transform.rotation = rigidBody.GetRotation();
        }
        else
        {
            rigidBody.SetRotation(transform.rotation);
        }
    }

    ptrPhysicScene->GetPhysicScene()->simulate(Time::deltaTime);
    ptrPhysicScene->GetPhysicScene()->fetchResults(true);
}

PhysicScene *PhysicsSystem::GetPhysicScene()
{
    return ptrPhysicScene;
};