#include "ECS/Components/ColliderComponent.hpp"
#include "Physic/PhysicCast.hpp"

using namespace BwatEngine;

// Cube Constructor
ColliderComponent::ColliderComponent(physx::PxMaterial* PMat, physx::PxBoxGeometry& Geo, Math::Transform& entityT)
{
	material = PMat;
	shape = Physic::GetPhysics()->createShape(physx::PxBoxGeometry(Geo.halfExtents.x, Geo.halfExtents.y, Geo.halfExtents.z), *material);
	//staticActor = Physic::GetPhysics()->createRigidDynamic(ToPxTransform(entityT));
	//staticActor->attachShape(*shape);
	type = COLLIDER_SHAPE_BOX;
}

// PLane Constructor
ColliderComponent::ColliderComponent(physx::PxMaterial* PMat, physx::PxBoxGeometry& Geo)
{
	material = PMat;
	//staticActor = physx::PxCreatePlane(*Physic::GetPhysics(), physx::PxPlane(0, 1, 0, 0), *material);
	type = COLLIDER_SHAPE_PLANE;
}

// Sphere Constructor
ColliderComponent::ColliderComponent(physx::PxMaterial* PMat, physx::PxBoxGeometry& Geo, Math::Transform& entityT, float radius)
{
	material = PMat;
	shape = Physic::GetPhysics()->createShape(physx::PxSphereGeometry(radius), *material);
	//staticActor = Physic::GetPhysics()->createRigidStatic(ToPxTransform(entityT));
	//staticActor->attachShape(*shape);
	type = COLLIDER_SHAPE_SPHERE;
}