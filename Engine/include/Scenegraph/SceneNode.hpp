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
        explicit SceneNode( BMath::Vector4<int> _colour = BMath::Vector4(1, 1, 1, 1));
        ~SceneNode();


        [[nodiscard]] BMath::Matrix4<float> GetWorldTransform() const;
        [[nodiscard]] const BMath::Matrix4<float>& GetTransform() const;
        void SetTransform (const BMath::Matrix4<float> &matrix);

        [[nodiscard]] BMath::Vector3<float> GetScale() const;
        void SetScale(BMath::Vector3<float> _scale);

        [[nodiscard]] BMath::Vector4<int> GetColour() const;
        void SetColour(BMath::Vector4<int> _colour);

        void AddChild(SceneNode* _child);

        virtual void Update(float DeltaTime);


        // if you want to have ref to first and last child uncomment this
        // std::Vector<SceneNode*>::const_iterator GetChildIteratorStart();
        // std::Vector<SceneNode*>::const_iterator GetChildIteratorEnd();

    protected :
        SceneNode* parent;
        BMath::Matrix4<float> worldTransform{};
        BMath::Matrix4<float> transform{};
        BMath::Vector3<float> modelScale{};
        BMath::Vector4<int> colour{};

        std::vector<SceneNode*> children;

    };
}
#endif