#include "Physic/PhysicScene.hpp"
#include "Physic/Physic.hpp"
#include <iostream>

#define STRINGIFY(input) #input

using namespace physx;
using namespace BwatEngine;


void ContactReportCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	contacts.push_back({ pairHeader, pairs[0].flags });
}

void ContactReportCallback::Flush()
{
	for (const Contact& contact : contacts)
	{
		BwatEngine::RigidBody& actor0 = *(BwatEngine::RigidBody*)contact.pairHeader.actors[0]->userData;
		BwatEngine::RigidBody& actor1 = *(BwatEngine::RigidBody*)contact.pairHeader.actors[1]->userData;

		if (contact.flags.isSet(PxContactPairFlag::Enum::eACTOR_PAIR_HAS_FIRST_TOUCH))
		{
			actor1.OnContact(actor0, COLLISION_TYPE::OnEnterCollision);
			actor0.OnContact(actor1, COLLISION_TYPE::OnEnterCollision);
		}

		actor1.OnContact(actor0, COLLISION_TYPE::OnStayCollision);
		actor0.OnContact(actor1, COLLISION_TYPE::OnStayCollision);

		if (contact.flags.isSet(PxContactPairFlag::Enum::eACTOR_PAIR_LOST_TOUCH))
		{
			actor1.OnContact(actor0, COLLISION_TYPE::OnExitCollision);
			actor0.OnContact(actor1, COLLISION_TYPE::OnExitCollision);
		}
	}

	contacts.clear();
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