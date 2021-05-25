#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include "Rendering/Animation.hpp"

using namespace BwatEngine;

namespace Rendering
{
    class Animator
    {
    public:

        Animator::Animator(Animation* Animation);

        void Animator::UpdateAnimation(float dt);
        void Animator::PlayAnimation(Animation* pAnimation);
        void Animator::CalculateBoneTransform(const AssimpNodeData* node, Math::Mat4f parentTransform);

        std::vector<Math::Mat4f> GetFinalBoneMatrices() { return finalBoneMatrices; };

    private:

        std::vector<Math::Mat4f> finalBoneMatrices;
        Animation* currentAnimation;
        float currentTime;
        float deltaTime;
    };
}

#endif // ANIMATOR_HPP