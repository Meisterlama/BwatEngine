#include "Physic/Collider.hpp"
#include "Physic/PhysicCast.hpp"
#include "PxShape.h"

using namespace BwatEngine;

// ================================ Mother Function ================================ //

void Collider::SetFriction(float friction)
{
	material->setStaticFriction(friction);
}

void Collider::SetIsTrigger(bool _isTrigger)
{
    if (_isTrigger != isTrigger)
    {
        if (_isTrigger)
        {
            shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
            shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
        }
        else
        {
            shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, false);
            shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, true);
        }
        isTrigger = _isTrigger;
    }
}

// ================================ Children Function ================================ // 

BoxCollider::BoxCollider(Math::Vec3f scale)
{
	material = Physic::GetPhysics()->createMaterial(0, 0, 0);
	shape = Physic::GetPhysics()->createShape(physx::PxBoxGeometry{ ToPxVec3(scale / 2.f) }, *material, true);
}

SphereCollider::SphereCollider(float radius)
{
	material = Physic::GetPhysics()->createMaterial(0, 0, 0);
	shape = Physic::GetPhysics()->createShape(physx::PxSphereGeometry(radius), *material, true);
}
