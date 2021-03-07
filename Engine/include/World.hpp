#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "Rendering/light.hpp"
#include "ECS/Entity.hpp"

class World
{
private:

	static std::vector<Rendering::Light> lights;

public:

	static void AddLight(Rendering::Light newlight);

	static std::vector<Rendering::Light>& GetWorldLights();
};

#endif // !WORLD_HPP
