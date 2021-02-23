#include "Scenegraph/SceneNode.hpp"

using namespace BSceneNode;

SceneNode::SceneNode( )
{
    parent = nullptr;
}

SceneNode::~SceneNode()
{
    for(auto & i : children)
        delete i;

}

BMath::Matrix4<float> SceneNode::GetWorldTransform() const
{
    return worldTransform;
}

const BMath::Matrix4<float>& SceneNode::GetTransform() const
{
    return transform;
}

void SceneNode::SetTransform (const BMath::Matrix4<float> &matrix)
{
    transform = matrix;
}

void SceneNode::AddChild(SceneNode *_child)
{
    children.push_back(_child);
    _child->parent = this;
}

void SceneNode::Update(float DeltaTime)
{
    if (parent)
        worldTransform = parent->worldTransform * transform;
    else
        worldTransform = transform;

    for(auto & i : children)
        i->Update(DeltaTime);
}

void SceneNode::Draw()
{

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
