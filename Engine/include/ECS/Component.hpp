#ifndef COMPONENT_HPP
#define COMPONENT_HPP
class Entity;

class Component
{
private:

	Entity* parent;

public:

	void SetParent(Entity* entity) { parent = entity; };
	Entity* GetParent() { return parent; };
	virtual void UpdateComponent() = 0;
};

#endif // !COMPONENT_HPP
