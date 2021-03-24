#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <random>

#include "Rendering/Light.hpp"
#include "Rendering/Model.hpp"
#include "ECS/Entity.hpp"
#include "Physic/Physic.hpp"


namespace BwatEngine
{
	class InputsSystem;
	class PhysicsSystem;
	class PlayerControlSystem;
	class RenderSystem;
	class Window;

	class Scene
	{
	private:

		static std::vector<Rendering::Light> lights;

	public:

		static void AddLight(Rendering::Light& newlight);
		static std::vector<Rendering::Light>& GetLights();

		Scene(Window& window);


		Rendering::Model model;

		std::vector<Entity> entities;

		std::shared_ptr<InputsSystem> inputSystem = nullptr;
		std::shared_ptr<PhysicsSystem> physicsSystem = nullptr;
		std::shared_ptr<PlayerControlSystem> playerControlSystem = nullptr;
		std::shared_ptr<RenderSystem> renderSystem = nullptr;

		// PhysX
		Physic physic{};
		physx::PxScene* scenePhysic;


	};

}
#endif // !WORLD_HPP
