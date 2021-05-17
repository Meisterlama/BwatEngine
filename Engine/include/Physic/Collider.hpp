#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <PxPhysicsAPI.h>

#include "Math/Math.hpp"
#include "Physic/Physic.hpp"

namespace BwatEngine
{
	class Collider
	{
	protected:

		physx::PxMaterial* material = nullptr;
		physx::PxShape* shape = nullptr;

	public:

		~Collider()
        {
		    if(material)
		        material->release();
		    if (shape)
		        shape->release();
        }
		physx::PxShape* GetShape() { return shape; }
        physx::PxMaterial* GetMaterial() { return material; }
		void SetFriction(float friction);

	};

	class BoxCollider : public Collider
	{
	public:
		BoxCollider(Math::Vec3f scale);
	};

	class SphereCollider : public Collider
	{
	public:
		SphereCollider(float radius);
	};
}

#endif // !COLLIDER_HPP