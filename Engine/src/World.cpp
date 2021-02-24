#include "World.hpp"

World::World(Rendering::Shader* shader)
{
	defaultShader = shader;
}

void World::UpdateEntities()
{
	for (Entity* entity : entities)
	{
		entity->UpdateAllComponent();
	}
}

void World::AddLight(Rendering::Light* newlight)
{
	lights.push_back(newlight);
}

void World::AddEntity(Entity* newEntity)
{
	entities.push_back(newEntity);
}

std::vector<Rendering::Light*> World::GetWorldLights()
{
	return lights;
}

Rendering::Shader* World::GetDefaultShader()
{
	return defaultShader;
}