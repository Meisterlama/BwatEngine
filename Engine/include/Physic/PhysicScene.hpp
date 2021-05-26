#ifndef PHYSICSCENE_HPP
#define PHYSICSCENE_HPP

#include "Physic/Physic.hpp"
#include "Physic/PhysicCast.hpp"
#include "PxSimulationEventCallback.h"
#include "Physic/RigidBody.hpp"

#include "ECS/ECS.hpp"

#include "Math/Vector/Vector3.hpp"

using namespace physx;

enum CollisionType {
    Unknown,
    Enter,
    Continue,
    Exit,
    TriggerEnter,
    TriggerExit,
};

struct Contact
{
    BwatEngine::EntityID otherEntity;
    CollisionType collisionType;
};

class ContactReportCallback : public PxSimulationEventCallback
{

private :

	bool enter = false; 

	void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) { PX_UNUSED(constraints); PX_UNUSED(count);}
	void onWake(PxActor** actors, PxU32 count) { PX_UNUSED(actors); PX_UNUSED(count);}
	void onSleep(PxActor** actors, PxU32 count) { PX_UNUSED(actors); PX_UNUSED(count);}
	void onTrigger(PxTriggerPair* pairs, PxU32 count);
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

	public:
	
		ContactReportCallback gContactReportCallback;

		void Init(Physic& physic);
		void SetGravity(Math::Vec3f gravity);
		physx::PxScene* GetPhysicScene() { return physicScene; }};
}


#endif //PHYSICSCENE_HPP