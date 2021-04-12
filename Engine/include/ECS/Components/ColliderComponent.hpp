#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include "Physic/Collider.hpp"

namespace BwatEngine
{
	struct ColliderComponent
	{
		Collider* collider = nullptr;
	};
}

#endif // !COLLIDERCOMPONENT_HPP
