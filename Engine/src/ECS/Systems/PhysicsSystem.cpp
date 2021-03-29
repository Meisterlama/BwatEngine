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

void PhysicsSystem::BeginSimulation()
{
}

void PhysicsSystem::SetColliderForRigidbody(Entity entity)
{
    //auto rigidComp = entity.GetComponent<RigidBodyComponent>();
    //auto colliderComp = entity.GetComponent<ColliderComponent>();
    //
    //rigidComp.rigidBody->attachShape(*colliderComp.shape);
}


void PhysicsSystem::Update()
{
    ptrScene->scenePhysic->simulate(Time::deltaTime);
    ptrScene->scenePhysic->fetchResults(true);

    //now, need an updats of entities
    //get all entities and refresh transform
    for (auto entity : entities)
    {
        auto& rigidBody = Coordinator::GetInstance()->GetComponent<RigidBodyComponent>(entity);
        auto& transform = Coordinator::GetInstance()->GetComponent<TransformComponent>(entity).transform;

        transform.position = ToBwatVec3(rigidBody.rigidBody->getGlobalPose().p);
        transform.rotation = ToBwatQuat(rigidBody.rigidBody->getGlobalPose().q);
    }
};