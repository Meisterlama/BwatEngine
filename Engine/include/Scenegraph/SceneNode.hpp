#ifndef SCENEGRAPH_SCENEGRAPH_HPP
#define SCENEGRAPH_SCENEGRAPH_HPP

#include <vector>
#include <memory>
#include "Math/Matrix/Matrix4.hpp"


class Entity
{
public:
    BwatEngine::Math::Mat4f worldTransform;
    BwatEngine::Math::Mat4f transform;
};

namespace BSceneNode
{
    class SceneNode
    {
    public:
        explicit SceneNode(Entity& _entity);
        ~SceneNode();

        SceneNode& AddChild(Entity& _child);

        void UpdateGraph(const BwatEngine::Math::Mat4f& parentWorldTransform);



        // if you want to have ref to first and last child uncomment this and in the .cpp
        // std::vector<SceneNode*>::const_iterator GetChildIteratorStart();
        // std::vector<SceneNode*>::const_iterator GetChildIteratorEnd();

    protected:
        std::vector<std::unique_ptr<SceneNode>> children;
        Entity& entity;
    };
}
#endif