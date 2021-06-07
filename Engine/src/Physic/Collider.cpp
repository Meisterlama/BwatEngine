#include "Physic/Collider.hpp"
#include "Physic/PhysicCast.hpp"
#include "PxShape.h"

using namespace BwatEngine;

// ================================ Mother Function ================================ //

Collider::Collider(Collider::ShapeType shapeType)
{
    material = Physic::GetPhysics()->createMaterial(0.1f, 0.5f, 0.05f);
    SetShape(shapeType);
}

const char *Collider::GetShapeTypeName(Collider::ShapeType _shapeType)
{
    switch (_shapeType)
    {
        case CUBE:
            return "Cube";
        case SPHERE:
            return "Sphere";
        case PLANE:
            return "Plane";
        case MESH:
            return "Mesh";
    }
}

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

void Collider::SetShape(Collider::ShapeType _shapeType)
{
    if (shape)
        shape->release();
    shapeType = _shapeType;
    switch (_shapeType)
    {
        case CUBE:
            shape = Physic::GetPhysics()->createShape(
                    physx::PxBoxGeometry{ ToPxVec3(0.5f) }, *material, true
            );
            break;
        case SPHERE:
            shape = Physic::GetPhysics()->createShape(
                    physx::PxSphereGeometry(1.0f), *material, true
            );
            break;
        case PLANE:
            shape = Physic::GetPhysics()->createShape(
                    physx::PxPlaneGeometry(), *material, true
            );
            break;
        case MESH:
            break;
    }
}

void Collider::SetBoxExtent(Math::Vec3f halfExtents)
{
    shape->setGeometry(physx::PxBoxGeometry{ ToPxVec3(halfExtents) });
}

Math::Vec3f Collider::GetBoxExtent() const
{
    return ToBwatVec3(shape->getGeometry().box().halfExtents);
}

void Collider::SetSphereRadius(float radius)
{
    shape->setGeometry(physx::PxSphereGeometry{radius});
}

float Collider::GetSphereRadius() const
{
    return shape->getGeometry().sphere().radius;
}
