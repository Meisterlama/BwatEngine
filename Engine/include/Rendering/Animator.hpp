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

        void UpdateAnimation(float dt);
        void PlayAnimation(Animation* pAnimation);
        void CalculateBoneTransform(const AssimpNodeData* node, Math::Mat4f parentTransform);

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