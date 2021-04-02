#include "Scenegraph/SceneNode.hpp"

using namespace BSceneNode;

SceneNode::SceneNode(Entity& _entity): entity(_entity)
{

}

SceneNode::~SceneNode()
{
}

SceneNode& SceneNode::AddChild(Entity& _child)
{
    children.push_back(std::make_unique<SceneNode>(_child));
    return *children.back();
}

void SceneNode::UpdateGraph(const BwatEngine::Math::Mat4f& parentWorldTransform)
{
    entity.worldTransform = parentWorldTransform * entity.transform;
    for (auto& child : children)
        child->UpdateGraph(entity.worldTransform);
}


/*
std::vector<SceneNode*>::const_iterator SceneNode::GetChildIteratorStart()
{
    return children.begin();
}

std::vector<SceneNode*>::const_iterator GetChildIteratorEnd()
{
    return children.end();
}
*/
