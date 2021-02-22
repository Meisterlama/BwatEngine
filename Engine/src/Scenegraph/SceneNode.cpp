#include "Scenegraph/SceneNode.hpp"

using namespace BSceneNode;

SceneNode::SceneNode( BMath::Vector4<int> _colour)
{
    colour = _colour;
    parent = nullptr;
    modelScale = BMath::Vector3<float>(1, 1, 1);
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

BMath::Vector3<float> SceneNode::GetScale() const
{
    return modelScale;
}

void SceneNode::SetScale(BMath::Vector3<float> _scale)
{
    modelScale = _scale;
}

BMath::Vector4<int> SceneNode::GetColour() const
{
    return colour;
}

void SceneNode::SetColour(BMath::Vector4<int> _colour)
{
    colour = _colour;
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

