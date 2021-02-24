#include "ECS/Entity.hpp"


void Entity::AddComponent(Component* tmpComp)
{
	myComponents.push_back(tmpComp);
}

void Entity::UpdateAllComponent()
{
	for (Component* component : myComponents)
	{
		component->UpdateComponent();
	}
}