#ifndef ANIMATOR_COMPONENT_HPP
#define ANIMATOR_COMPONENT_HPP

#include "Rendering/Animator.hpp"

namespace BwatEngine
{
	struct AnimatorComponent
	{
		AnimatorComponent() = default;

		Rendering::Animation animation;
		Rendering::Animator animator;

		bool needLink = false;
		bool isValid = false;
		std::string pathAnimation;
	};

}

#endif // !ANIMATOR_COMPONENT_HPP
