#include "Physic/Physic.hpp"
#include "Debug/Logger.hpp"

using namespace BwatEngine;
using namespace physx;

PxPhysics* Physic::gPhysics = nullptr;

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


	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true);
	PxInitExtensions(*gPhysics, nullptr);

	PxU32 numCores = 1;
	gDispatcher = PxDefaultCpuDispatcherCreate(1);

	if (!PxInitExtensions(*gPhysics, gPvd))
		LogError("PxCreatePhysics failed!");;
	
	if(gFoundation && gPhysics )
		LogInfo("[PhysX] PxCreatePhysics succes!");
	else
		LogError("[PhysX] PxCreatePhysics failed!");;
}

Physic::~Physic()
{
	if (gDispatcher)
		gDispatcher->release();
	if (gPhysics)
		gPhysics->release();
	if (gPvd)
		gPvd->release();
	if (gFoundation)
		gFoundation->release();
}

