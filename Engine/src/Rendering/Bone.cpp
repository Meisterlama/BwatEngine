#include "Rendering/Bone.hpp"
#include "Debug/Logger.hpp"
#include "Math/Vector/Vector3.hpp"

using namespace Rendering;

Math::Vec3f GetBwatVec(const aiVector3D& vec)
{
    return Math::Vec3f(vec.x, vec.y, vec.z);
}

Math::Quatf GetBwatQuat(const aiQuaternion& pOrientation)
{
    return Math::Quatf(pOrientation.w, pOrientation.x, pOrientation.y, pOrientation.z);
}

Bone::Bone(const std::string& name, int ID, const aiNodeAnim* channel):
    name(name),
    iD(ID),
    localTransform(1.0f)
{
    numPositions = channel->mNumPositionKeys;

    for (int positionIndex = 0; positionIndex < numPositions; ++positionIndex)
    {
        aiVector3D aiPosition = channel->mPositionKeys[positionIndex].mValue;
        float timeStamp = channel->mPositionKeys[positionIndex].mTime;
        KeyPosition data;
        data.position = GetBwatVec(aiPosition);
        data.timeStamp = timeStamp;
        positionsK.push_back(data);
    }

    numRotations = channel->mNumRotationKeys;
    for (int rotationIndex = 0; rotationIndex < numRotations; ++rotationIndex)
    {
        aiQuaternion aiOrientation = channel->mRotationKeys[rotationIndex].mValue;
        float timeStamp = channel->mRotationKeys[rotationIndex].mTime;
        KeyRotation data;
        data.orientation = GetBwatQuat(aiOrientation);
        data.timeStamp = timeStamp;
        rotationsK.push_back(data);
    }

    numScalings = channel->mNumScalingKeys;
    for (int keyIndex = 0; keyIndex < numScalings; ++keyIndex)
    {
        aiVector3D scale = channel->mScalingKeys[keyIndex].mValue;
        float timeStamp = channel->mScalingKeys[keyIndex].mTime;
        KeyScale data;
        data.scale = GetBwatVec(scale);
        data.timeStamp = timeStamp;
        scalesK.push_back(data);
    }
}

void Bone::Update(float animationTime)
{
    Math::Mat4f translation = InterpolatePosition(animationTime);
    Math::Mat4f rotation = InterpolateRotation(animationTime);
    Math::Mat4f scale = InterpolateScaling(animationTime);
    localTransform = translation * rotation * scale;
}

int Bone::GetPositionIndex(float animationTime)
{
    for (int index = 0; index < numPositions - 1; ++index)
    {
        if (animationTime < positionsK[index + 1].timeStamp)
            return index;
    }
    LogError("Bone Position wrong !");
}

int Bone::GetRotationIndex(float animationTime)
{
    for (int index = 0; index < numRotations - 1; ++index)
    {
        if (animationTime < rotationsK[index + 1].timeStamp)
            return index;
    }
    LogError("Bone Rotation wrong !");

}

int Bone::GetScaleIndex(float animationTime)
{
    for (int index = 0; index < numScalings - 1; ++index)
    {
        if (animationTime < scalesK[index + 1].timeStamp)
            return index;
    }
    LogError("Bone Scale wrong !");

}

float Bone::GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
{
    float scaleFactor = 0.0f;
    float midWayLength = animationTime - lastTimeStamp;
    float framesDiff = nextTimeStamp - lastTimeStamp;
    scaleFactor = midWayLength / framesDiff;
    return scaleFactor;
}

/* figures out which position keys to interpolate b/w and performs the interpolation
and returns the translation matrix */
Math::Mat4f Bone::InterpolatePosition(float animationTime)
{
    if (1 == numPositions)
        return Math::Mat4f::CreateTranslationMat(positionsK[0].position); // need to check

    int p0Index = GetPositionIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor = GetScaleFactor(positionsK[p0Index].timeStamp,
        positionsK[p1Index].timeStamp, animationTime);
    Math::Vec3f finalPosition = Lerp(positionsK[p0Index].position, positionsK[p1Index].position , scaleFactor);

    return Math::Mat4f::CreateTranslationMat(finalPosition);
}

/* figures out which rotations keys to interpolate b/w and performs the interpolation
and returns the rotation matrix */
Math::Mat4f Bone::InterpolateRotation(float animationTime)
{
    if (1 == numRotations)
    {
        auto rotation = Math::Quatf(rotationsK[0].orientation).GetNormalized();
        return Math::Mat4f::CreateRotationMat(rotation);
    }

    int p0Index = GetRotationIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor = GetScaleFactor(rotationsK[p0Index].timeStamp,
        rotationsK[p1Index].timeStamp, animationTime);
    Math::Quatf finalRotation = Math::SLerp(rotationsK[p0Index].orientation,rotationsK[p1Index].orientation, scaleFactor);
    finalRotation = finalRotation.GetNormalized();

    return Math::Mat4f::CreateRotationMat(finalRotation);
}

/* figures out which scaling keys to interpolate b/w and performs the interpolation
and returns the scale matrix */
Math::Mat4f Bone::InterpolateScaling(float animationTime)
{
    if (1 == numScalings)
        return  Math::Mat4f::CreateScaleMat(scalesK[0].scale);

    int p0Index = GetScaleIndex(animationTime);
    int p1Index = p0Index + 1;
    float scaleFactor = GetScaleFactor(scalesK[p0Index].timeStamp,
        scalesK[p1Index].timeStamp, animationTime);
    Math::Vec3f finalScale = Lerp(scalesK[p0Index].scale, scalesK[p1Index].scale, scaleFactor);

    return  Math::Mat4f::CreateScaleMat(finalScale);
}