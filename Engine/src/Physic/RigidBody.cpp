#include "ECS/Coordinator.hpp"
#include "Physic/RigidBody.hpp"
#include "ECS/Systems/PhysicsSystem.hpp"

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
    shouldRegister = true;
}

RigidBody::~RigidBody()
{
	if (isStatic && staticActor && staticActor->isReleasable())
		staticActor->release();
	else if (rigidBody && rigidBody->isReleasable())
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

void RigidBody::SetPosition(const Math::Vec3f &position)
{
    oldTransform.position = position;
    if (isStatic)
        staticActor->setGlobalPose(ToPxTransform(oldTransform));
    else
        rigidBody->setGlobalPose(ToPxTransform(oldTransform));
}
void RigidBody::SetRotation(const Math::Quatf &rotation)
{
    oldTransform.rotation = rotation;
    if (isStatic)
        staticActor->setGlobalPose(ToPxTransform(oldTransform));
    else
        rigidBody->setGlobalPose(ToPxTransform(oldTransform));
}

void RigidBody::SetMass(const float mass)
{
	if (!isStatic)
		rigidBody->setMass(mass);
}

void RigidBody::AddActor(PhysicScene* scene)
{
	if (isStatic)
		scene->GetPhysicScene()->addActor(*staticActor);
	else
		scene->GetPhysicScene()->addActor(*rigidBody);

    shouldRegister = false;
}

bool RigidBody::CompareOldPosition(const Math::Vec3f & position) const
{
	return (oldTransform.position == position);
}

bool RigidBody::CompareOldRotation(const Math::Quatf & rotation) const
{
	return (oldTransform.rotation == rotation);
}

Math::Vec3f RigidBody::GetPosition() const
{
	if (isStatic)
		return ToBwatVec3( staticActor->getGlobalPose().p);
	else
		return ToBwatVec3(rigidBody->getGlobalPose().p);
}

Math::Quatf RigidBody::GetRotation() const
{
	if (isStatic)
		return ToBwatQuat(staticActor->getGlobalPose().q);
	else
		return ToBwatQuat(rigidBody->getGlobalPose().q);
}


float RigidBody::GetMass() const
{
	if (!isStatic)
		return rigidBody->getMass();
	return 0;
}

Math::Vec3f RigidBody::GetVelocity() const
{
	if (!isStatic)
		return ToBwatVec3(rigidBody->getLinearVelocity());
	return {0.f};
}
void RigidBody::LockRotation(bool _lockX, bool _lockY, bool _lockZ)
{
    if (isStatic)
        return;

    lockX = _lockX;
    lockY = _lockY;
    lockZ = _lockZ;

    PxRigidDynamicLockFlags lockFlags;
    if (lockX)
        lockFlags |= PxRigidDynamicLockFlag::eLOCK_ANGULAR_X;
    if (lockY)
        lockFlags |= PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y;
    if (lockZ)
        lockFlags |= PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z;

    rigidBody->setRigidDynamicLockFlags(lockFlags);
}
