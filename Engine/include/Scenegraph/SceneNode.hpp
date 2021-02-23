#ifndef SCENEGRAPH_SCENEGRAPH_HPP
#define SCENEGRAPH_SCENEGRAPH_HPP

#include <vector>
#include "Math/Matrix/Matrix4.hpp"
#include "Math/Vector/Vector4.hpp"

namespace BSceneNode
{
    class SceneNode
    {
    public:
        explicit SceneNode();
        ~SceneNode();

        [[nodiscard]] BMath::Matrix4<float> GetWorldTransform() const;
        [[nodiscard]] const BMath::Matrix4<float>& GetTransform() const;
        void SetTransform (const BMath::Matrix4<float> &matrix);


        void AddChild(SceneNode* _child);

        virtual void Update(float DeltaTime);
        virtual void Draw();


        // if you want to have ref to first and last child uncomment this and in the .cpp
        // std::Vector<SceneNode*>::const_iterator GetChildIteratorStart();
        // std::Vector<SceneNode*>::const_iterator GetChildIteratorEnd();

    protected :
        SceneNode* parent;
        BMath::Matrix4<float> worldTransform{};
        BMath::Matrix4<float> transform{};

        std::vector<SceneNode*> children;

    };
}
#endif