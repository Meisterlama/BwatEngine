#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include <iostream>

#include "Math/Math.hpp"
#include "Component.hpp"

struct Transform
{
	BMath::vec3f position;
	BMath::vec3f rotation;
	BMath::vec3f scale;
};

class Entity
{

private:

	Transform myTransform;
	std::vector<Component*> myComponents;

public :

	Entity() {};

	void AddComponent(Component* tmpComp);
	void UpdateAllComponent();
	
};

#endif // !ENTITY_HPP
