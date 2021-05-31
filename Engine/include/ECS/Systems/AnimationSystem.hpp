#ifndef ANIMATION_SYSTEM_HPP
#define ANIMATION_SYSTEM_HPP

#include "ECS/System.hpp"
#include "ECS/ECS.hpp"
#include "ECS/Coordinator.hpp"


namespace BwatEngine
{
	class AnimationSystem : public System
	{
	public:
		
		AnimationSystem();
		virtual void Update() override;


	private:

		EntityID cameraID = 0;
		Signature signature;
	};

}

#endif // !ANIMATION_SYSTEM_HPP
