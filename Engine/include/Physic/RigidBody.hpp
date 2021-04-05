#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include <PxPhysicsAPI.h>

#include "PhysicCast.hpp"
#include "Math/Math.hpp"
#include "Physic.hpp"
#include "Collider.hpp"

namespace BwatEngine 
{
	class RigidBody 
	{

	private :

		physx::PxRigidBody* rigidBody = nullptr;
		physx::PxRigidStatic* staticActor = nullptr;
		bool isStatic = false;
		bool shouldRegister = true;
		Math::Transform oldTransform{};

	public :

		RigidBody(const Math::Transform& transform = {}, bool isStatic = false);
		~RigidBody(); // rule of three -> https://en.cppreference.com/w/cpp/language/rule_of_three

		void SetStatic(bool isStat);
		void AttachCollider(Collider& collider);
		void SetVelocity(const Math::Vec3f& vec);
		void AddForce(const Math::Vec3f& vec);
		void SetTransform(const Math::Transform& trans);
		void SetMass(const float mass);
		void AddActor(physx::PxScene* scene);

		bool CompareOldTransform(const Math::Transform& trans);
		bool GetIsStatic() { return isStatic; }
		bool ShouldRegister() { return shouldRegister; }

		Math::Vec3f GetPosition();
		Math::Quatf GetRotation();

		float GetMass();
		Math::Vec3f GetVelocity();

	};
}

#endif // !RIGIDBODY_HPP
