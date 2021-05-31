#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <PxPhysicsAPI.h>

#include "Math/Math.hpp"
#include "Physic/Physic.hpp"

namespace BwatEngine
{
	class Collider
	{
    public:
        enum ShapeType {
            CUBE,
            SPHERE,
            PLANE,
            MESH,
            SIZE,
        };
	private:

		physx::PxMaterial* material = nullptr;
		physx::PxShape* shape = nullptr;
        bool isTrigger = false;
        ShapeType shapeType;

    public:

	    Collider(ShapeType shapeType = CUBE);
		~Collider()
        {
		    if(material)
		        material->release();
		    if (shape)
		        shape->release();
        }
		physx::PxShape* GetShape() const { return shape; }
        physx::PxMaterial* GetMaterial() const { return material; }
        bool GetIsTrigger() { return isTrigger; }
        ShapeType GetShapeType() { return shapeType; }
        static const char* GetShapeTypeName(ShapeType _shapeType);
        void SetFriction(float friction);
        void SetIsTrigger(bool _isTrigger);
        void SetShape(ShapeType shapeType = CUBE);
	};
}

#endif // !COLLIDER_HPP