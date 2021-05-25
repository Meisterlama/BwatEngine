#include "Rendering/Animator.hpp"

using namespace Rendering;

Animator::Animator(Animation* Animation)
{
    currentTime = 0.0;
    currentAnimation = currentAnimation;

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

    auto boneInfoMap = currentAnimation->GetBoneIDMap();
    if (boneInfoMap.find(nodeName) != boneInfoMap.end())
    {
        int index = boneInfoMap[nodeName].id;
        Math::Mat4f offset = boneInfoMap[nodeName].offset;
        finalBoneMatrices[index] = globalTransformation * offset;
    }

    for (int i = 0; i < node->childrenCount; i++)
        CalculateBoneTransform(&node->children[i], globalTransformation);
}

