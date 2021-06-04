#include "Rendering/Animator.hpp"

using namespace Rendering;

Animator::Animator(Animation* animation)
{
    currentTime = 0.0;
    currentAnimation = animation;

    finalBoneMatrices.reserve(100);

    for (int i = 0; i < 100; i++)
        finalBoneMatrices.push_back(Math::Mat4f(1.0f));
}

void Animator::UpdateAnimation(float dt)
{
    deltaTime = dt;
    if (currentAnimation)
    {
        currentTime += currentAnimation->GetTicksPerSecond() * dt;
        currentTime = fmod(currentTime, currentAnimation->GetDuration());
        CalculateBoneTransform(&currentAnimation->GetRootNode(), Math::Mat4f(1.0f));
    }
}

void Animator::PlayAnimation(Animation* pAnimation)
{
    currentAnimation = pAnimation;
    currentTime = 0.0f;
}

void Animator::CalculateBoneTransform(const AssimpNodeData* node, Math::Mat4f parentTransform)
{
    std::string nodeName = node->name;
    Math::Mat4f nodeTransform = node->transformation;

    Bone* Bone = currentAnimation->FindBone(nodeName);

    if (Bone)
    {
        Bone->Update(currentTime);
        nodeTransform = Bone->GetLocalTransform();
    }

    Math::Mat4f globalTransformation = parentTransform * nodeTransform;

    BoneInfo* boneInfo = currentAnimation->FindBoneInfo(nodeName);
    if (boneInfo)
    {
        int index = boneInfo->id;
        Math::Mat4f offset = boneInfo->offset;
        finalBoneMatrices[index] = globalTransformation * offset;
    }

    for (int i = 0; i < node->childrenCount; i++)
        CalculateBoneTransform(&node->children[i], globalTransformation);
}

void Animator::ClearAnimation()
{
    currentAnimation = nullptr;
    currentTime = 0.0f;
}