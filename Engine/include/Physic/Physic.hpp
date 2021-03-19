#ifndef PHYSIC_HPP
#define PHYSIC_HPP

#include <PxPhysicsAPI.h>
#include <iostream>
#include <string>

namespace BwatEngine
{

	class Physic
	{
	public:
		Physic();
		~Physic();

		physx::PxFoundation* GetFoundation() { return gFoundation; }
		static physx::PxPhysics* GetPhysics() { return gPhysics; }
		physx::PxCooking* GetCooking() { return gCooking; }
		physx::PxCpuDispatcher* GetCPUDispatcher() { return gDispatcher; }

	private:

		physx::PxDefaultAllocator gAllocator;
		physx::PxDefaultCpuDispatcher* gDispatcher = nullptr;
		physx::PxFoundation* gFoundation = nullptr;
		static physx::PxPhysics* gPhysics;
		physx::PxCooking* gCooking = nullptr;
		physx::PxPvd* gPvd = nullptr;

	};

	

}
#endif // !Physic
