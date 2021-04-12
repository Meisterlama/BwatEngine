#ifndef PHYSICSCENE_HPP
#define PHYSICSCENE_HPP

#include <vector>

#include "Math/Vector/Vector3.hpp"
#include "Physic/Physic.hpp"

namespace BwatEngine
{
	
	class PhysicScene
	{
	private:

		physx::PxScene* physicScene;
		Math::Vec3f gravity{ 0, -10, 0 };

	public:
	
		void Init(Physic& physic);
		void SetGravity(Math::Vec3f gravity);
		physx::PxScene* GetPhysicScene() { return physicScene; }
	};
}


#endif //PHYSICSCENE_HPP