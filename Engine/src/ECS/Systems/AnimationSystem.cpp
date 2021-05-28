#include "ECS/Systems/AnimationSystem.hpp"
#include "Time.hpp"
#include "ECS/Components/AnimatorComponent.hpp"
#include "ECS/Components/RenderableComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/CameraComponent.hpp"


using namespace BwatEngine;

AnimationSystem::AnimationSystem()
{
	signature.set(Coordinator::GetInstance().GetComponentType<CameraComponent>());
	signature.set(Coordinator::GetInstance().GetComponentType<TransformComponent>());

}

void AnimationSystem::Update()
{
	auto& coordinator = Coordinator::GetInstance();

	for (auto entity : entities)
	{
		auto& component = coordinator.GetComponent<AnimatorComponent>(entity);
		auto& rendComponent = coordinator.GetComponent<RenderableComponent>(entity);

		if (component.needLink)
		{
			component.animation = { component.pathAnimation , rendComponent.model }; 
			component.needLink = false;
			component.isValid = true;
			component.animator.PlayAnimation(&component.animation);
		}

		if (component.isValid)	
			component.animator.UpdateAnimation(Time::deltaTime * component.speedAnimation);
	}

}