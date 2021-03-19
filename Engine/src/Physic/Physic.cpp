#include "Physic/Physic.hpp"
#include "Debug/Logger.hpp"

using namespace BwatEngine;
using namespace physx;

class BwatPXErrorCallback : public physx::PxErrorCallback
{
public:
	virtual void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override
	{
		LogError("[PhysX] Error Code: %i, Details: %s" , code, message);
	}
}gErrorCallback;

Physic::Physic()
{
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true);
	PxInitExtensions(*gPhysics, nullptr);
	
	gCooking = PxCreateCooking(PX_PHYSICS_VERSION, *gFoundation, PxCookingParams(gPhysics->getTolerancesScale()));

	PxU32 numCores = 4;
	gDispatcher = PxDefaultCpuDispatcherCreate(numCores == 0 ? 0 : numCores - 1);


	if (!PxInitExtensions(*gPhysics, gPvd))
		LogError("PxCreatePhysics failed!");;
	
	if(gFoundation && gPhysics && gCooking)
		LogInfo("[PhysX] PxCreatePhysics succes!");
	else
		LogError("[PhysX] PxCreatePhysics failed!");;
}

Physic::~Physic()
{
	gDispatcher->release();
	gCooking->release();
	gPhysics->release();
	gFoundation->release();
}

