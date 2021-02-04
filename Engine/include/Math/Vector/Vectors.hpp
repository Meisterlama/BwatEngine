#ifndef MATH_VECTORS_HPP
#define MATH_VECTORS_HPP

#include "Math/Meta.hpp"

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace Math
{
    typedef Vector2<float> vec2f;
    typedef Vector2<signed int> vec2i;
    typedef Vector2<unsigned int> vec2u;

    typedef Vector3<float> vec3f;
    typedef Vector3<signed int> vec3i;
    typedef Vector3<unsigned int> vec3u;

    typedef Vector4<float> vec4f;
    typedef Vector4<signed int> vec4i;
    typedef Vector4<unsigned int> vec4u;
}

#endif //MATH_VECTORS_HPP