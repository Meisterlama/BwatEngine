#include "Physic\Collider.hpp"

using namespace BwatEngine;

// ================================ Mother Function ================================ //


void Collider::SetFriction(float friction)
{
	material->setStaticFriction(friction);
}


// ================================ Children Function ================================ // 

BoxCollider::BoxCollider(Math::Vec3f scale)
{
	material = Physic::GetPhysics()->createMaterial(0, 0, 0);
	shape = Physic::GetPhysics()->createShape(physx::PxBoxGeometry{ ToPxVec3(scale / 2.f) }, *material);
}

SphereCollider::SphereCollider(float radius)
{
	material = Physic::GetPhysics()->createMaterial(0, 0, 0);
	shape = Physic::GetPhysics()->createShape(physx::PxSphereGeometry(radius), *material);
}
