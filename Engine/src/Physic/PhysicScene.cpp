#include "Physic/PhysicScene.hpp"
#include "Physic/Physic.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Components/ScriptComponent.hpp"

using namespace physx;
using namespace BwatEngine;


void ContactReportCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
    auto& coordinator = BwatEngine::Coordinator::GetInstance();

    BwatEngine::RigidBody& actor0 = *(BwatEngine::RigidBody*)pairHeader.actors[0]->userData;
    BwatEngine::RigidBody& actor1 = *(BwatEngine::RigidBody*)pairHeader.actors[1]->userData;

    BwatEngine::EntityID entity0 = coordinator.GetEntityIDFrom(actor0);
    BwatEngine::EntityID entity1 = coordinator.GetEntityIDFrom(actor1);

    CollisionType collisionType;

    if (pairs[0].flags.isSet(PxContactPairFlag::Enum::eACTOR_PAIR_HAS_FIRST_TOUCH))
    {
        collisionType = Enter;
    }
    else if (pairs[0].flags.isSet(PxContactPairFlag::Enum::eACTOR_PAIR_LOST_TOUCH))
    {
        collisionType = Exit;
    }
    else
    {
        collisionType = Continue;
    }

    if (coordinator.HaveComponent<ScriptComponent>(entity0))
    {
        coordinator.GetComponent<ScriptComponent>(entity0).contacts.push_back(
                Contact{
                    entity1,
                    collisionType,
                });
    }
    if (coordinator.HaveComponent<ScriptComponent>(entity1))
    {
        coordinator.GetComponent<ScriptComponent>(entity1).contacts.push_back(
                Contact{
                    entity0,
                    collisionType,
                });
    }
}

void ContactReportCallback::onTrigger(PxTriggerPair *pairs, PxU32 count)
{
    auto& coordinator = BwatEngine::Coordinator::GetInstance();
    for (PxU32 i = 0; i < count; i++)
    {
        BwatEngine::RigidBody& actor0 = *(BwatEngine::RigidBody*)pairs[i].triggerActor->userData;
        BwatEngine::RigidBody& actor1 = *(BwatEngine::RigidBody*)pairs[i].otherActor->userData;

        BwatEngine::EntityID entity0 = coordinator.GetEntityIDFrom(actor0);
        BwatEngine::EntityID entity1 = coordinator.GetEntityIDFrom(actor1);

        CollisionType collisionType;

        if (pairs[i].status == physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
        {
            collisionType = TriggerEnter;
        }
        else if (pairs[i].status == physx::PxPairFlag::eNOTIFY_TOUCH_LOST)
        {
            collisionType = TriggerExit;
        }

        if (coordinator.HaveComponent<ScriptComponent>(entity0))
        {
            coordinator.GetComponent<ScriptComponent>(entity0).contacts.push_back(
                    Contact{
                            entity1,
                            collisionType,
                    });
        }
        if (coordinator.HaveComponent<ScriptComponent>(entity1))
        {
            coordinator.GetComponent<ScriptComponent>(entity1).contacts.push_back(
                    Contact{
                            entity0,
                            collisionType,
                    });
        }
    }
}

PxFilterFlags contactReportFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	PX_UNUSED(attributes0);
	PX_UNUSED(attributes1);
	PX_UNUSED(filterData0);
	PX_UNUSED(filterData1);
	PX_UNUSED(constantBlockSize);
	PX_UNUSED(constantBlock);

    if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
    {
        pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
        return PxFilterFlag::eDEFAULT;
    }

	// all initial and persisting reports for everything, with per-point data
	pairFlags = PxPairFlag::eSOLVE_CONTACT | PxPairFlag::eDETECT_DISCRETE_CONTACT
		| PxPairFlag::eNOTIFY_TOUCH_FOUND
		| PxPairFlag::eNOTIFY_TOUCH_PERSISTS
		| PxPairFlag::eNOTIFY_CONTACT_POINTS 
		| PxPairFlag::eNOTIFY_TOUCH_LOST; 
	return PxFilterFlag::eDEFAULT;
}


void PhysicScene::Init(Physic& physic)
{

    physx::PxSceneDesc SceneDesc(Physic::GetPhysics()->getTolerancesScale());
    SceneDesc.gravity = ToPxVec3(gravity);
    SceneDesc.cpuDispatcher = physic.GetCPUDispatcher();
    SceneDesc.filterShader = contactReportFilterShader;
    SceneDesc.simulationEventCallback = &gContactReportCallback;

    physicScene = (Physic::GetPhysics()->createScene(SceneDesc));
}

void PhysicScene::SetGravity(Math::Vec3f grav)
{
    gravity = grav;
}