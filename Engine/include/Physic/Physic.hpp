#ifndef PHYSIC_HPP
#define PHYSIC_HPP

#include <PxPhysicsAPI.h>

// these include are not used
#include <iostream> 
#include <string>

namespace BwatEngine
{

	class Physic
	{
	public:
		Physic();
		~Physic(); // rule of three -> https://en.cppreference.com/w/cpp/language/rule_of_three

		physx::PxFoundation* GetFoundation() { return gFoundation; }
		static physx::PxPhysics* GetPhysics() { return gPhysics; }
		//physx::PxCooking* GetCooking() { return gCooking; }
		physx::PxCpuDispatcher* GetCPUDispatcher() { return gDispatcher; }

	private:

		physx::PxDefaultAllocator gAllocator;
		physx::PxDefaultCpuDispatcher* gDispatcher = nullptr;
		physx::PxFoundation* gFoundation = nullptr;
		static physx::PxPhysics* gPhysics;
		//physx::PxCooking* gCooking = nullptr;
		physx::PxPvd* gPvd = nullptr;

	};

	

}
#endif // !Physic
