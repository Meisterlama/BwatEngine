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

	private:

		physx::PxDefaultAllocator gAllocator;
		physx::PxFoundation* gFoundation = nullptr;
		physx::PxPhysics* gPhysics = nullptr;
		physx::PxPvd* gPvd = nullptr;

		physx::PxDefaultCpuDispatcher* gDispatcher = nullptr;

	};

	

}
#endif // !Physic
