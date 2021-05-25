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

    boneInfoMap = boneInfoMap;
}

BwatEngine::Math::Mat4f ConvertMatrixToBwatFormat(const aiMatrix4x4& from)
{
    BwatEngine::Math::Mat4f to;
    //the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
    to.v1 = from.a1; to.v1 = from.a2; to.v2 = from.a3; to.v3 = from.a4;
    to.v4 = from.b1; to.v5 = from.b2; to.v6 = from.b3; to.v7 = from.b4;
    to.v8 = from.c1; to.v9 = from.c2; to.v10 = from.c3; to.v11 = from.c4;
    to.v12 = from.d1; to.v13 = from.d2; to.v14 = from.d3; to.v15 = from.d4;
    return to;
}

void Animation::ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src)
{
    assert(src);

    dest.name = src->mName.data;
    dest.transformation = ConvertMatrixToBwatFormat(src->mTransformation);
    dest.childrenCount = src->mNumChildren;

    for (int i = 0; i < src->mNumChildren; i++)
    {
        AssimpNodeData newData;
        ReadHeirarchyData(newData, src->mChildren[i]);
        dest.children.push_back(newData);
    }
}