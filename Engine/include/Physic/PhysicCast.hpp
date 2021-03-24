#ifndef PHYSICCAST_HPP
#define PHYSICCAST_HPP

#include <PxPhysicsAPI.h>
#include "Math/Math.hpp"

namespace BwatEngine
{
	inline physx::PxVec3 ToPxVec3(const Math::Vec3f& v)
	{
		return physx::PxVec3(v.X, v.Y, v.Z);
	}

	inline physx::PxVec4 ToPxVec4(const Math::Vec4f& v)
	{
		return physx::PxVec4(v.X, v.Y, v.Z, v.W);
	}

	inline physx::PxTransform ToPxTransform(const Math::Transform& trans)
	{
		return physx::PxTransform(ToPxVec3(trans.position));
	}

	inline Math::Vec3f ToBwatVec3(const physx::PxVec3& v)
	{
		return Math::Vec3f(v.x, v.y, v.z);
	}
}

#endif // !PHYSICCAST_HPP
