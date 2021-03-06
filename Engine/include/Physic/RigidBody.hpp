#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include <PxPhysicsAPI.h>

#include "PhysicCast.hpp"
#include "Math/Math.hpp"
#include "Physic.hpp"
#include "Collider.hpp"

namespace BwatEngine 
{
    class PhysicScene;
	class RigidBody
	{
	private :

		physx::PxRigidDynamic* rigidBody = nullptr;
		physx::PxRigidStatic* staticActor = nullptr;
		bool isStatic = false;
		bool shouldRegister = true;
		Math::Transform oldTransform{};

		bool lockX = false;
		bool lockY = false;
		bool lockZ = false;

	public :

		RigidBody(const Math::Transform& transform = {}, bool isStatic = false);
		~RigidBody();

		void SetStatic(bool isStat);
		void AttachCollider(Collider& collider);
		void SetVelocity(const Math::Vec3f& vec);
		void AddForce(const Math::Vec3f& vec);
		void SetTransform(const Math::Transform& trans);
		void SetPosition(const Math::Vec3f & position);
		void SetRotation(const Math::Quatf & rotation);
		void SetMass(const float mass);
		void AddActor(PhysicScene* scene);

		void LockRotation(bool lockX, bool lockY, bool lockZ);
		bool GetXLockState() const { return lockX; }
		bool GetYLockState() const { return lockY; }
		bool GetZLockState() const { return lockZ; }

        bool CompareOldPosition(const Math::Vec3f &position) const;
        bool CompareOldRotation(const Math::Quatf &rotation) const;
        bool GetIsStatic() const { return isStatic; }
		bool ShouldRegister() { return shouldRegister; }

		Math::Vec3f GetPosition()const;
		Math::Quatf GetRotation() const;

		float GetMass() const;
		Math::Vec3f GetVelocity() const;
    };
}

#endif // !RIGIDBODY_HPP
