#include "Physic/RigidBody.hpp"

using namespace BwatEngine;

RigidBody::RigidBody(const Math::Transform& transform, bool isStatic) : isStatic(isStatic)
{
	if (isStatic)
		staticActor = Physic::GetPhysics()->createRigidStatic(ToPxTransform(transform));
	else
		rigidBody = Physic::GetPhysics()->createRigidDynamic(ToPxTransform(transform));
}

RigidBody::~RigidBody()
{
	//if (isStatic)
	//	staticActor->release();
	//else
	//	rigidBody->release();
}

void RigidBody::AttachCollider(Collider& collider)
{
	if (isStatic)
	{
		staticActor->attachShape(*collider.GetShape());
	}
	else
	{
		rigidBody->attachShape(*collider.GetShape());
	}
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