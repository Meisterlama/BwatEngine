#include "Physic/PhysicScene.hpp"
#include "Physic/PhysicCast.hpp"
#include "Physic/Physic.hpp"
#include "PxSimulationEventCallback.h"

using namespace physx;

std::vector<PxVec3> gContactPositions;
std::vector<PxVec3> gContactImpulses;

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
		| PxPairFlag::eNOTIFY_CONTACT_POINTS;
	return PxFilterFlag::eDEFAULT;
}

class ContactReportCallback : public PxSimulationEventCallback
{
	void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) { PX_UNUSED(constraints); PX_UNUSED(count); }
	void onWake(PxActor** actors, PxU32 count) { PX_UNUSED(actors); PX_UNUSED(count); }
	void onSleep(PxActor** actors, PxU32 count) { PX_UNUSED(actors); PX_UNUSED(count); }
	void onTrigger(PxTriggerPair* pairs, PxU32 count) { PX_UNUSED(pairs); PX_UNUSED(count); }
	void onAdvance(const PxRigidBody* const*, const PxTransform*, const PxU32) {}
	void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
	{
		PX_UNUSED((pairHeader));
		std::vector<PxContactPairPoint> contactPoints;

		for (PxU32 i = 0; i < nbPairs; i++)
		{
			PxU32 contactCount = pairs[i].contactCount;
			if (contactCount)
			{
				contactPoints.resize(contactCount);
				pairs[i].extractContacts(&contactPoints[0], contactCount);

				for (PxU32 j = 0; j < contactCount; j++)
				{
					gContactPositions.push_back(contactPoints[j].position);
					gContactImpulses.push_back(contactPoints[j].impulse);
				}
			}
		}
	}
};


ContactReportCallback gContactReportCallback;

using namespace BwatEngine;

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