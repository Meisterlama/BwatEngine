#include "ECS/Systems/PhysicsSystem.hpp"
#include "Time.hpp"

using namespace BwatEngine;

void PhysicsSystem::Init(Scene* scene, const Math::Vec3f& gravity)  
{
    ptrScene = scene;

    physx::PxSceneDesc SceneDesc(ptrScene->physic.GetPhysics()->getTolerancesScale());
    SceneDesc.gravity = *(physx::PxVec3*) &gravity;
    SceneDesc.cpuDispatcher = ptrScene->physic.GetCPUDispatcher();
    SceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;

    ptrScene->scenePhysic = (ptrScene->physic.GetPhysics()->createScene(SceneDesc));
}

void PhysicsSystem::BeginSimulation()
{
    ptrScene->scenePhysic->simulate(Time::deltaTime);
}

void PhysicsSystem::Update()
{
    ptrScene->scenePhysic->fetchResults(true);

    //now, need an updats of entities

    /*for (auto entityID : entities)
    {
        Entity entity{ entityID };
        auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
        auto& transform = entity.GetComponent<TransformComponent>().transform;
        auto const& gravity = entity.GetComponent<GravityComponent>();

        transform.position += rigidBody.velocity * Time::deltaTime;
        rigidBody.velocity += gravity.force * Time::deltaTime;
    }*/
};