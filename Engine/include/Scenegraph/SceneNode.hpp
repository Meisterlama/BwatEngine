#ifndef SCENEGRAPH_SCENEGRAPH_HPP
#define SCENEGRAPH_SCENEGRAPH_HPP

#include <vector>
#include <memory>
#include "Math/Matrix/Matrix4.hpp"


class Entity
{
public:
    BMath::Matrix4<float> worldTransform;
    BMath::Matrix4<float> transform;
};

namespace BSceneNode
{
    class SceneNode
    {
    public:
        explicit SceneNode(Entity& _entity);
        ~SceneNode();

        SceneNode& AddChild(Entity& _child);

        void UpdateGraph(const BMath::Matrix4<float>& parentWorldTransform);



        // if you want to have ref to first and last child uncomment this and in the .cpp
        // std::Vector<SceneNode*>::const_iterator GetChildIteratorStart();
        // std::Vector<SceneNode*>::const_iterator GetChildIteratorEnd();

    protected:
        std::vector<std::unique_ptr<SceneNode>> children;
        Entity& entity;
    };
}
#endif