#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "Rendering/Light.hpp"
#include "ECS/Entity.hpp"
#include <PxPhysicsAPI.h>

#include <random>

namespace BwatEngine
{
	class InputsSystem;
	class PhysicsSystem;
	class PlayerControlSystem;
	class RenderSystem;

	class Scene
	{
	private:

		static std::vector<Rendering::Light> lights;

	public:

		static void AddLight(Rendering::Light& newlight);
		static std::vector<Rendering::Light>& GetLights();

		Scene();

		Physic physic{};

		Rendering::Model model;

		std::vector<Entity> entities;

		std::shared_ptr<InputsSystem> inputSystem = nullptr;
		std::shared_ptr<PhysicsSystem> physicsSystem = nullptr;
		std::shared_ptr<PlayerControlSystem> playerControlSystem = nullptr;
		std::shared_ptr<RenderSystem> renderSystem = nullptr;
	};

}
#endif // !WORLD_HPP
