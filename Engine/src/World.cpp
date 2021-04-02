#include "World.hpp"

std::vector<Rendering::Light> World::lights;

void World::AddLight(Rendering::Light& newlight)
{
	lights.push_back(newlight);
}

std::vector<Rendering::Light>& World::GetWorldLights()
{
	return lights;
}