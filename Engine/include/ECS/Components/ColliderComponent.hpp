#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include "Physic/Collider.hpp"

namespace BwatEngine
{
	struct ColliderComponent
	{
		Collider* collider = nullptr;

		ColliderComponent(Math::Vec3f scale = {1.0f}) // Cube
        {
            collider = new BoxCollider{scale};
        }

        ColliderComponent(float radius) // Sphere
        {
            collider = new SphereCollider{radius};
        }

        ~ColliderComponent()
        {
            if (collider)
            {
                delete collider;
                collider = nullptr;
            }
        }
	};


}

#endif // !COLLIDERCOMPONENT_HPP
