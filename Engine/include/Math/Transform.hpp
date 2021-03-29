#ifndef ENGINE_MATH_TRANSFORM_HPP
#define ENGINE_MATH_TRANSFORM_HPP

#include "Math/Vector/Vector3.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Matrix/Matrix4.hpp"

#pragma region Declarations
namespace BwatEngine::Math
{
    class Transform
    {
    public:
        Vec3f position{ 0 };
        Quatf rotation{ 1, 0, 0, 0 };
        Vec3f scale{ 1 };

        Transform(Vec3f _position, Vec3f _rotation, Vec3f _scale)
        : position(_position),
          rotation(_rotation),
          scale(_scale) {};

        Transform(Vec3f _position = { 0 }, Quatf _rotation = { 0 }, Vec3f _scale = { 1 })
            : position(_position),
            rotation(_rotation),
            scale(_scale) {};

        Mat4f GetTRS();
    };
}
#pragma endregion

#ifdef BMATH_IMPLEMENTATION
#pragma region Definitions
namespace BwatEngine::Math
{
    Mat4f Transform::GetTRS()
    {
        return Mat4f::CreateTRSMat(position, rotation, scale);
    }
}
#pragma endregion
#endif//BMATH_IMPLEMENTATION

#endif //ENGINE_MATH_TRANSFORM_HPP