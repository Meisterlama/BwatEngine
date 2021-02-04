#ifndef MATH_NOISE_HPP
#define MATH_NOISE_HPP

#include "Math/Meta.hpp"

namespace Math {
    // Based on Math for Game Programmers: Noise-Based RNG from GDC 2017

    [[nodiscard]] ML_FUNC_DECL
    unsigned int Get1dNoiseUint(unsigned int posX,
                                unsigned int seed = 0);
    [[nodiscard]] ML_FUNC_DECL
    unsigned int Get2dNoiseUint(unsigned int posX, unsigned int posY,
                                unsigned int seed = 0);
    [[nodiscard]] ML_FUNC_DECL
    unsigned int Get3dNoiseUint(unsigned int posX, unsigned int posY, unsigned int posZ,
                                unsigned int seed = 0);
    [[nodiscard]] ML_FUNC_DECL
    unsigned int Get4dNoiseUint(unsigned int posX, unsigned int posY, unsigned int posZ, unsigned int posW,
                                unsigned int seed = 0);

    [[nodiscard]] ML_FUNC_DECL
    float Get1dNoiseZeroToOne(unsigned int posX,
                              unsigned int seed = 0);
    [[nodiscard]] ML_FUNC_DECL
    float Get2dNoiseZeroToOne(unsigned int posX, unsigned int posY,
                              unsigned int seed = 0);
    [[nodiscard]] ML_FUNC_DECL
    float Get3dNoiseZeroToOne(unsigned int posX, unsigned int posY, unsigned int posZ,
                              unsigned int seed = 0);
    [[nodiscard]] ML_FUNC_DECL
    float Get4dNoiseZeroToOne(unsigned int posX, unsigned int posY, unsigned int posZ, unsigned int posW,
                              unsigned int seed = 0);

    [[nodiscard]] ML_FUNC_DECL
    float Get1dNoiseNegOneToOne(unsigned int posX,
                                unsigned int seed = 0);
    [[nodiscard]] ML_FUNC_DECL
    float Get2dNoiseNegOneToOne(unsigned int posX, unsigned int posY,
                                unsigned int seed = 0);
    [[nodiscard]] ML_FUNC_DECL
    float Get3dNoiseNegOneToOne(unsigned int posX, unsigned int posY, unsigned int posZ,
                                unsigned int seed = 0);
    [[nodiscard]] ML_FUNC_DECL
    float Get4dNoiseNegOneToOne(unsigned int posX, unsigned int posY, unsigned int posZ, unsigned int posW,
                                unsigned int seed = 0);

    #include "inl/Noise.inl.hpp"
}
#endif //MATH_NOISE_HPP
