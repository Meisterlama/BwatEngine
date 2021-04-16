#ifndef PHYSICSCENE_HPP
#define PHYSICSCENE_HPP

#include <vector>
#include "Physic/Physic.hpp"
#include "Physic/PhysicCast.hpp"
#include "PxSimulationEventCallback.h"
#include "Physic/RigidBody.hpp"
#include "Debug/Logger.hpp"

#include "Math/Vector/Vector3.hpp"

using namespace physx;


class ContactReportCallback : public PxSimulationEventCallback
{
	bool enter = false; 

	void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) { PX_UNUSED(constraints); PX_UNUSED(count);}
	void onWake(PxActor** actors, PxU32 count) { PX_UNUSED(actors); PX_UNUSED(count);}
	void onSleep(PxActor** actors, PxU32 count) { PX_UNUSED(actors); PX_UNUSED(count);}
	void onTrigger(PxTriggerPair* pairs, PxU32 count) { PX_UNUSED(pairs); PX_UNUSED(count);}
	void onAdvance(const PxRigidBody* const*, const PxTransform*, const PxU32) {}
	void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);
};

namespace BwatEngine
{
	
	class PhysicScene
	{
	private:

		physx::PxScene* physicScene;
		Math::Vec3f gravity{ 0, -10, 0 };

		ContactReportCallback gContactReportCallback;


	public:
	
		void Init(Physic& physic);
		void SetGravity(Math::Vec3f gravity);
		physx::PxScene* GetPhysicScene() { return physicScene; }
	};
}


#endif //PHYSICSCENE_HPP