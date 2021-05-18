#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "Rendering/Light.hpp"
#include "Rendering/Model.hpp"
#include "Physic/Physic.hpp"
#include "Physic/PhysicScene.hpp"


namespace BwatEngine
{
	class Window;


	class Scene
	{
	private:


	public:

		Scene(Window& window);
        Rendering::Material myMat;
        Rendering::Material myMat1;

		// PhysX
		Physic physic{};
		PhysicScene scenePhysic;
	};

}
#endif // !WORLD_HPP
