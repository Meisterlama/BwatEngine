#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include <iostream>

#include "Math/Math.hpp"
#include "Component.hpp"

struct Transform
{
	BMath::vec3f position{ 0 };
	BMath::vec3f rotation{ 0 };
	BMath::vec3f scale{ 1 };
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
	Transform& GetTransform() { return myTransform; };
	void SetTransform(Transform transform) { myTransform = transform; };
	
};

#endif // !ENTITY_HPP
