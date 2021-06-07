#include "ECS/Components/AnimatorComponent.hpp"
#include "Debug/Logger.hpp"

using namespace BwatEngine;

void AnimatorComponent::SetNewAnimation(std::string name, std::string pathAnim)
{
	if (model == nullptr)
	{
		LogError("Set Model of animator first !");
		return;
	}

	// check same name 
	for (std::string nam : names)
	{
		if (nam == name)
		{
			LogError("Animation name already exist");
			return;
		}
	}

	names.push_back(name);
	animations.push_back({ pathAnim,model });

	if(isValid)
		animator.PlayAnimation(&animations[indexSave]);
}

void AnimatorComponent::SetAnimationModel(Rendering::Model* mod)
{
	if(model != mod)
		model = mod;
}

void AnimatorComponent::PlayAnimation(std::string name)
{

	for (int i = 0; i < names.size(); i++)
	{
		if (name == names[i])
		{
			animator.PlayAnimation(&animations[i]);
			isValid = true;
			indexSave = i;
		}
	}
}

void AnimatorComponent::DeleteAnimation(std::string name)
{
	
	for (int i = 0; i < names.size(); i++)
	{
		if (name == names[i])
		{
			if (i == indexSave)
			{
				indexSave = -1;
				isValid = false;
				animator.ClearAnimation();
			}
			if (indexSave == names.size() - 1)
			{
				indexSave = i;
				PlayAnimation(names[indexSave]);
			}

			animations[i] = animations.back();
			animations.pop_back();

			names[i] = names.back();
			names.pop_back();
		}
	}


	if (names.size() <= 0)
		isValid = false;
}