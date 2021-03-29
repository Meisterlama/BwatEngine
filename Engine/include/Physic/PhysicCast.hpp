#ifndef PHYSICCAST_HPP
#define PHYSICCAST_HPP

#include <PxPhysicsAPI.h>
#include "Math/Math.hpp"

namespace BwatEngine
{
	// =================================== Bwat to PhysX =================================== // 

	inline physx::PxVec3 ToPxVec3(const Math::Vec3f& v)
	{
		return physx::PxVec3(v.X, v.Y, v.Z);
	}

	inline physx::PxVec4 ToPxVec4(const Math::Vec4f& v)
	{
		return physx::PxVec4(v.X, v.Y, v.Z, v.W);
	}

	inline physx::PxQuat ToPxQuat(const Math::Quatf& q)
	{
		return physx::PxQuat(q.X, q.Y, q.Z, q.W);
	}

	inline physx::PxTransform ToPxTransform(const Math::Transform& trans)
	{
		return physx::PxTransform(ToPxVec3(trans.position),ToPxQuat(trans.rotation));
	}

	// =================================== PhysX to Bwat =================================== //
	
	inline Math::Quatf ToBwatQuat(const physx::PxQuat& q)
	{
		return Math::Quatf(q.w, q.x, q.y, q.z);
	}

	inline Math::Vec3f ToBwatVec3(const physx::PxVec3& v)
	{
		return Math::Vec3f(v.x, v.y, v.z);
	}

	inline Math::Transform ToBwatTransform(const physx::PxTransform& trans)
	{
		return Math::Transform(ToBwatVec3(trans.p), ToBwatQuat(trans.q), {1});
	}
}

#endif // !PHYSICCAST_HPP
