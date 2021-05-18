#ifndef PHYSIC_HPP
#define PHYSIC_HPP

#include <PxPhysicsAPI.h>

namespace BwatEngine
{

	class Physic
	{
	public:
		Physic();
		~Physic();

		physx::PxFoundation* GetFoundation() { return gFoundation; }
		static physx::PxPhysics* GetPhysics() { return gPhysics; }
		physx::PxCpuDispatcher* GetCPUDispatcher() { return gDispatcher; }

	private:

		physx::PxDefaultAllocator gAllocator;
		physx::PxDefaultCpuDispatcher* gDispatcher = nullptr;
		physx::PxFoundation* gFoundation = nullptr;
		static physx::PxPhysics* gPhysics;
		physx::PxPvd* gPvd = nullptr;

	};

	

}
#endif // !Physic
