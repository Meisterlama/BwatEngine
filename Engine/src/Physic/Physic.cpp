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
	
	//Tool of debug for PhysX
	//gPvd = PxCreatePvd(*gFoundation);
	//PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true);
	PxInitExtensions(*gPhysics, nullptr);

	PxU32 numCores = 4;
	gDispatcher = PxDefaultCpuDispatcherCreate(numCores == 0 ? 0 : numCores - 1);
	
	if(gFoundation && gPhysics)
		LogInfo("[PhysXEngine] PhysX has been initalized succesfully!");
}

Physic::~Physic()
{
	gDispatcher->release();
	gPhysics->release();
	gFoundation->release();
}


