#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "Rendering/Light.hpp"

class World
{
private:

	static std::vector<Rendering::Light> lights;

public:

	static void AddLight(Rendering::Light& newlight);

	static std::vector<Rendering::Light>& GetWorldLights();
};

#endif // !WORLD_HPP
