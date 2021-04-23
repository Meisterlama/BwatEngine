#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <random>

#include "Rendering/Light.hpp"
#include "Rendering/Model.hpp"
#include "Physic/Physic.hpp"
#include "ECS/ECS.hpp"
#include "Physic/PhysicScene.hpp"


namespace BwatEngine
{
	class InputsSystem;
	class PhysicsSystem;
	class PlayerControlSystem;
	class RenderSystem;
	class ScriptSystem;
	class SoundSystem;
	class Window;
	class PostProcessSystem;

	class Scene
	{
	private:


	public:

		Scene(Window& window);

		// TODO : resrc manager to load rsrc and stock
		Rendering::Model* model;
		Rendering::Texture* texture;
		Rendering::Texture* texture1;
		Rendering::Material myMat;
		Rendering::Material myMat1;

		std::shared_ptr<PhysicsSystem> physicsSystem = nullptr;
		std::shared_ptr<PlayerControlSystem> playerControlSystem = nullptr;
		std::shared_ptr<RenderSystem> renderSystem = nullptr;
		std::shared_ptr<SoundSystem> soundSystem = nullptr;
		std::shared_ptr<ScriptSystem> scriptSystem = nullptr;
		std::shared_ptr<PostProcessSystem> postProcessSystem = nullptr;

		// PhysX
		Physic physic{};
		PhysicScene scenePhysic;
	};

}
#endif // !WORLD_HPP
