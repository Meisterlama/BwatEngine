#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include "Math/Transform.hpp"
#include "Math/Matrix/Matrices.hpp"

namespace BSceneNode
{
    class SceneNode;
}
class Component;
class Entity
{

private:

	BwatEngine::Math::Transform localTransform{};
	BwatEngine::Math::Mat4f globalTransform = localTransform.GetTRS();
	std::vector<Component*> myComponents{};
    BSceneNode::SceneNode* node = nullptr;

public :

	Entity() {};

	void AddComponent(Component* tmpComp);
	void UpdateAllComponent();
    BwatEngine::Math::Transform& GetLocalTransform() { return localTransform; };
	void SetTransform(BwatEngine::Math::Transform transform) { localTransform = transform; };
	
};

#endif // !ENTITY_HPP
