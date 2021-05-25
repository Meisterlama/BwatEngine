#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "Rendering/Model.hpp"
#include "Rendering/Bone.hpp"

using namespace BwatEngine;
namespace Rendering
{

    struct AssimpNodeData
    {
        Math::Mat4f transformation;
        std::string name;
        int childrenCount;
        std::vector<AssimpNodeData> children;
    };

    class Animation
    {
    public:

        Animation() = default;
        Animation(const std::string& animationPath, Model* model);

        ~Animation() {};

        Bone* FindBone(const std::string& name);

        inline float GetTicksPerSecond() { return ticksPerSecond; }
        inline float GetDuration() { return duration; }
        inline const AssimpNodeData& GetRootNode() { return rootNode; }
        inline const std::map<std::string, BoneInfo>& GetBoneIDMap(){ return boneInfoMap;}

    private:

        void ReadMissingBones(const aiAnimation* animation, Model& model);
        void ReadHeirarchyData(AssimpNodeData& dest, const aiNode* src);

        float duration;
        int ticksPerSecond;
        std::vector<Bone> bones;
        AssimpNodeData rootNode;
        std::map<std::string, BoneInfo> boneInfoMap;
    };
}

#endif 