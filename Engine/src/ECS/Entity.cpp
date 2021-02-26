#include "ECS/Entity.hpp"


void Entity::AddComponent(Component* tmpComp)
{
	tmpComp->SetParent(this);
	myComponents.push_back(tmpComp);
}

void Entity::UpdateAllComponent()
{
	for (Component* component : myComponents)
	{
		component->UpdateComponent();
	}
}