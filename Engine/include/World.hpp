#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "Rendering/light.hpp"
#include "ECS/Entity.hpp"

class World
{
private:

	static std::vector<Rendering::Light*> lights;
	static Rendering::Shader* defaultShader;

	std::vector<Entity*> entities;

public:

	World(Rendering::Shader* defaultShader);

	void AddLight(Rendering::Light* newlight);
	void AddEntity(Entity* newEntity);
	void UpdateEntities();

	static Rendering::Shader* GetDefaultShader();
	static std::vector<Rendering::Light*>& GetWorldLights();
	std::vector<Entity*>& GetWorldEntities();
};

#endif // !WORLD_HPP
