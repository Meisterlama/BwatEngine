#ifndef ANIMATOR_COMPONENT_HPP
#define ANIMATOR_COMPONENT_HPP

#include "Rendering/Animator.hpp"

namespace BwatEngine
{
	struct AnimatorComponent
	{
		AnimatorComponent() = default;

		Rendering::Animator animator;

		Rendering::Model* model = nullptr;

		std::vector<Rendering::Animation> animations;
		std::vector<std::string> names;

		bool isValid = false;
		float speedAnimation = 30.f;
		int indexSave = -1;

		void SetNewAnimation(std::string name, std::string pathAnim );
		void SetAnimationModel(Rendering::Model* model);
		void PlayAnimation(std::string name);
		void DeleteAnimation(std::string name);
	};

}

#endif // !ANIMATOR_COMPONENT_HPP
