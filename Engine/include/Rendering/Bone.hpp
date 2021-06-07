#ifndef BONE_HPP
#define BONE_HPP

#include "Math/Math.hpp"
#include <vector>
#include <string>


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace BwatEngine;
namespace Rendering 
{
    struct KeyPosition
    {
        Math::Vec3f position;
        float timeStamp;
    };

    struct KeyRotation
    {
        Math::Quatf orientation;
        float timeStamp;
    };

    struct KeyScale
    {
        Math::Vec3f scale;
        float timeStamp;
    };

	class Bone
	{
    private:

        std::vector<KeyPosition> positionsK;
        std::vector<KeyRotation> rotationsK;
        std::vector<KeyScale> scalesK;

        int numPositions;
        int numRotations;
        int numScalings;

        Math::Mat4f localTransform;
        std::string name;
        int iD;

    public:

        Bone(const std::string& name, int ID, const aiNodeAnim* channel);
        /* Interpolates b/w positions,rotations & scaling keys based on the curren time of the
        animation and prepares the local transformation matrix by combining all keys tranformations */
        void Update(float animationTime);
      

        Math::Mat4f GetLocalTransform() { return localTransform; }
        std::string GetBoneName() const { return name; }
        int GetBoneID() { return iD; }

        /* Gets the current index on mKeyPositions to interpolate to based on the current
        animation time */
        int GetPositionIndex(float animationTime);
        /* Gets the current index on mKeyRotations to interpolate to based on the current
        animation time */
        int GetRotationIndex(float animationTime);
        /* Gets the current index on mKeyScalings to interpolate to based on the current
        animation time */
        int GetScaleIndex(float animationTime);

    private:

        /* Gets normalized value for Lerp & Slerp*/
        float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);

        /* figures out which position keys to interpolate b/w and performs the interpolation
        and returns the translation matrix */
        Math::Mat4f InterpolatePosition(float animationTime);

        /* figures out which rotations keys to interpolate b/w and performs the interpolation
        and returns the rotation matrix */
        Math::Mat4f InterpolateRotation(float animationTime);
        

        /* figures out which scaling keys to interpolate b/w and performs the interpolation
        and returns the scale matrix */
        Math::Mat4f InterpolateScaling(float animationTime);
	};
	
}

#endif 