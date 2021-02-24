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

void SceneNode::UpdateGraph(const BMath::Matrix4<float>& parentWorldTransform)
{
    entity.worldTransform = parentWorldTransform * entity.transform;
    for (auto& child : children)
        child->UpdateGraph(entity.worldTransform);
}


/*
std::Vector<SceneNode*>::const_iterator SceneNode::GetChildIteratorStart()
{
    return children.begin();
}

std::Vector<SceneNode*>::const_iterator GetChildIteratorEnd()
{
    return children.end();
}
*/
