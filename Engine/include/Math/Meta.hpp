#ifndef MATH_META_HPP
#define MATH_META_HPP

// Inline definition
#ifdef INLINE_FUNCTIONS
#define ML_INLINE inline
#else
#define ML_INLINE
#endif

// Concatenate constexpr and eventual inline
#define ML_FUNC_DECL ML_INLINE

namespace BwatEngine::Math
{
    // Magic numbers

    constexpr float PI = 3.1415926535897932;

    constexpr float EPSILON = 0.00000001;
}

#endif //MATH_META_HPP
