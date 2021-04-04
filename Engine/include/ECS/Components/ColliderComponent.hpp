#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include "Physic/Collider.hpp"

namespace BwatEngine
{
	struct ColliderComponent
	{
		// I strongly advise you to initialize your pointer to nullptr
		// when declaring them. It is an easy way to reduce the risk of bug
		Collider* collider;
	};
}

#endif // !COLLIDERCOMPONENT_HPP
