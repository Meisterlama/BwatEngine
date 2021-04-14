#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <random>

#include "Rendering/Light.hpp"
#include "Rendering/Model.hpp"
#include "Physic/Physic.hpp"
#include "ECS/ECS.hpp"


namespace BwatEngine
{
	class InputsSystem;
	class PhysicsSystem;
	class PlayerControlSystem;
	class RenderSystem;
	class ScriptSystem;
	class SoundSystem;
	class Window;

	class Scene
	{
	private:

		static std::vector<Rendering::Light> lights;

	public:

		static void AddLight(Rendering::Light& newlight);
		static std::vector<Rendering::Light>& GetLights();

		Scene(Window& window);

		// TODO : resrc manager to load rsrc and stock
		Rendering::Model model;
		Rendering::Texture texture;
		Rendering::Texture texture1;
		Rendering::Material myMat;
		Rendering::Material myMat1;

		std::vector<EntityID> entities;

		std::shared_ptr<InputsSystem> inputSystem = nullptr;
		std::shared_ptr<PhysicsSystem> physicsSystem = nullptr;
		std::shared_ptr<PlayerControlSystem> playerControlSystem = nullptr;
		std::shared_ptr<RenderSystem> renderSystem = nullptr;
		std::shared_ptr<SoundSystem> soundSystem = nullptr;
		std::shared_ptr<ScriptSystem> scriptSystem = nullptr;

		// PhysX
		Physic physic{};
		physx::PxScene* scenePhysic;


	};

}
#endif // !WORLD_HPP
