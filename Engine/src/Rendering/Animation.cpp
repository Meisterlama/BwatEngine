#include "Rendering/Animation.hpp"
#include "Rendering/Model.hpp"
#include "Debug/Logger.hpp"

#include <cassert>

using namespace Rendering;


Animation::Animation(const std::string& animationPath, Rendering::Model* model)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);

    assert(scene && scene->mRootNode);

    auto animation = scene->mAnimations[0];
    duration = animation->mDuration;
    ticksPerSecond = animation->mTicksPerSecond;
    ReadHeirarchyData(rootNode, scene->mRootNode);
    ReadMissingBones(animation, *model);
    path = animationPath;
}


Bone* Animation::FindBone(const std::string& name)
{
    auto iter = std::find_if(bones.begin(), bones.end(),[&](const Bone& Bone)
        {
            return Bone.GetBoneName() == name;
        }
    );

    if (iter == bones.end()) 
        return nullptr;
    else 
        return &(*iter);
}

BoneInfo* Animation::FindBoneInfo(const std::string& name)
{
    auto found = allBoneInfoMap.find(name);
    return (found != allBoneInfoMap.end()) ? &found->second : nullptr;
}

void Animation::ReadMissingBones(const aiAnimation* animation, Rendering::Model& model)
{
    int size = animation->mNumChannels;

    auto& boneInfoMap = model.GetBoneInfoMap();//getting m_BoneInfoMap from Model class
    int& boneCount = model.GetBoneCount(); //getting the m_BoneCounter from Model class

    //reading channels(bones engaged in an animation and their keyframes)
    for (int i = 0; i < size; i++)
    {
        auto channel = animation->mChannels[i];
        std::string boneName = channel->mNodeName.data;

        if (boneInfoMap.find(boneName) == boneInfoMap.end())
        {
            boneInfoMap[boneName].id = boneCount;
            boneCount++;
        }
        bones.push_back(Bone(channel->mNodeName.data,
            boneInfoMap[channel->mNodeName.data].id, channel));
    }

    allBoneInfoMap = boneInfoMap;
}

static BwatEngine::Math::Mat4f ConvertMatrixToBFormat(const aiMatrix4x4& from)
{
    BwatEngine::Math::Mat4f to;
    memcpy(to.values, &from.a1, sizeof(BwatEngine::Math::Mat4f));
    return to.GetTransposed();
}

void Animation::ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src)
{
    assert(src);

    if (src == nullptr)
        return;

    dest.name = src->mName.data;
    dest.transformation = ConvertMatrixToBFormat(src->mTransformation);
    dest.childrenCount = src->mNumChildren;

    for (int i = 0; i < src->mNumChildren; i++)
    {
        AssimpNodeData newData;
        ReadHeirarchyData(newData, src->mChildren[i]);
        dest.children.push_back(newData);
    }
}