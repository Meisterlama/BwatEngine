#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include <PxPhysicsAPI.h>

#include "PhysicCast.hpp"
#include "Math/Math.hpp"
#include "Physic.hpp"
#include "Collider.hpp"

#include <functional>

namespace BwatEngine 
{

	enum COLLISION_TYPE
	{
		OnEnterCollision,
		OnStayCollision,
		OnExitCollision,
		EnumSize,
	};

	class RigidBody 
	{

		typedef std::function<void(RigidBody&)> OnCollisionFunction;

	private :

		physx::PxRigidBody* rigidBody = nullptr;
		physx::PxRigidStatic* staticActor = nullptr;
		bool isStatic = false;
		bool shouldRegister = true;
		Math::Transform oldTransform{};

		OnCollisionFunction collisionFunction[COLLISION_TYPE::EnumSize]{};

	public :

		RigidBody(const Math::Transform& transform = {}, bool isStatic = false);
		~RigidBody();

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

		void OnContact(RigidBody& actor2, COLLISION_TYPE colType);
		void setContactFunc(COLLISION_TYPE colType, OnCollisionFunction&& func);
		

	};
}

#endif // !RIGIDBODY_HPP
