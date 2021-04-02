#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include <PxPhysicsAPI.h>

#include "Physic/Physic.hpp"
#include "Math/Transform.hpp"

namespace BwatEngine
{
	enum COLLIDER_SHAPE
	{
		COLLIDER_SHAPE_UNKNOWN,
		COLLIDER_SHAPE_BOX,
		COLLIDER_SHAPE_PLANE,
		COLLIDER_SHAPE_SPHERE
	};

	struct ColliderComponent
	{
		ColliderComponent() = default;
		// Cube Constructor
		ColliderComponent(physx::PxMaterial* PMat, physx::PxBoxGeometry& Geo, Math::Transform& entityT);
		// PLane Constructor
		ColliderComponent(physx::PxMaterial* PMat, physx::PxBoxGeometry& Geo);
		// Sphere Constructor
		ColliderComponent(physx::PxMaterial* PMat, physx::PxBoxGeometry& Geo, Math::Transform& entityT, float radius);

		COLLIDER_SHAPE type = COLLIDER_SHAPE_UNKNOWN;
		physx::PxMaterial* material = nullptr;
		physx::PxShape* shape = nullptr;
		//physx::PxRigidDynamic* staticActor = nullptr;
	};
}

#endif // !COLLIDERCOMPONENT_HPP
