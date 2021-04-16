#include "Physic/RigidBody.hpp"

using namespace BwatEngine;

RigidBody::RigidBody(const Math::Transform& transform, bool isStatic) : oldTransform(transform), isStatic(isStatic)
{
	if (isStatic)
	{
		staticActor = Physic::GetPhysics()->createRigidStatic(ToPxTransform(transform));
		staticActor->userData = this;
	}
	else
	{
		rigidBody = Physic::GetPhysics()->createRigidDynamic(ToPxTransform(transform));
		rigidBody->userData = this;
	}
}

RigidBody::~RigidBody()
{
	if (isStatic)
		staticActor->release();
	else
		rigidBody->release();
}

void RigidBody::SetStatic(bool isStat)
{
	if (isStatic == isStat)
		return;

	if (isStat)
	{
		isStatic = true;

		if (rigidBody)
		{
			rigidBody->release();
			rigidBody = nullptr;

		}

		staticActor = Physic::GetPhysics()->createRigidStatic(ToPxTransform(oldTransform));
		staticActor->userData = this;
	}
	else
	{
		isStatic = false;

		if (staticActor)
		{
			staticActor->release();
			staticActor = nullptr;
		}

		rigidBody = Physic::GetPhysics()->createRigidDynamic(ToPxTransform(oldTransform));
		rigidBody->userData = this;
	}

	shouldRegister = true;
}

void RigidBody::AttachCollider(Collider& collider)
{
	if (isStatic)
		staticActor->attachShape(*collider.GetShape());
	else
		rigidBody->attachShape(*collider.GetShape());
}

void RigidBody::SetVelocity(const Math::Vec3f& vec)
{
	if (!isStatic)
		rigidBody->setLinearVelocity(ToPxVec3(vec));
}

void RigidBody::AddForce(const Math::Vec3f& vec)
{
	if (!isStatic)
		rigidBody->addForce(ToPxVec3(vec));
}

void RigidBody::SetTransform(const Math::Transform& trans)
{
	oldTransform = trans;

	if (isStatic)
		staticActor->setGlobalPose(ToPxTransform(trans));
	else
		rigidBody->setGlobalPose(ToPxTransform(trans));
}

void RigidBody::SetMass(const float mass)
{
	if (!isStatic)
		rigidBody->setMass(mass);
}

void RigidBody::AddActor(physx::PxScene* scene)
{
	if (isStatic)
		scene->addActor(*staticActor);
	else
		scene->addActor(*rigidBody);

	shouldRegister = false;
}

bool RigidBody::CompareOldTransform(const Math::Transform& trans)
{
	return (oldTransform.position == trans.position && oldTransform.rotation == trans.rotation);
}

Math::Vec3f RigidBody::GetPosition()
{
	if (isStatic)
		return ToBwatVec3( staticActor->getGlobalPose().p);
	else
		return ToBwatVec3(rigidBody->getGlobalPose().p);
}

Math::Quatf RigidBody::GetRotation()
{
	if (isStatic)
		return ToBwatQuat(staticActor->getGlobalPose().q);
	else
		return ToBwatQuat(rigidBody->getGlobalPose().q);
}


float RigidBody::GetMass()
{
	if (!isStatic)
		return rigidBody->getMass();
}

Math::Vec3f RigidBody::GetVelocity()
{
	if (!isStatic)
		return ToBwatVec3(rigidBody->getLinearVelocity());
}

void RigidBody::OnContact(RigidBody& actor2, COLLISION_TYPE colType)
{
	if (collisionFunction[colType]) collisionFunction[colType](actor2);
}

void RigidBody::setContactFunc(COLLISION_TYPE colType, OnCollisionFunction&& func)
{
	collisionFunction[colType] = std::move(func);
}