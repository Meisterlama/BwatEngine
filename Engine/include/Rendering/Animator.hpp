#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include "Rendering/Animation.hpp"

using namespace BwatEngine;

namespace Rendering
{
    class Animator
    {
    public:

        Animator(Animation* Animation = nullptr);

        void Animator::UpdateAnimation(float dt);
        void Animator::PlayAnimation(Animation* pAnimation);
        void Animator::CalculateBoneTransform(const AssimpNodeData* node, Math::Mat4f parentTransform);

        const std::vector<Math::Mat4f>& GetFinalBoneMatrices() { return finalBoneMatrices; };
        void ClearAnimation();

    private:

        std::vector<Math::Mat4f> finalBoneMatrices;
        Animation* currentAnimation;
        float currentTime = 0.f;
        float deltaTime = 0.f;
    };
}

#endif // ANIMATOR_HPP