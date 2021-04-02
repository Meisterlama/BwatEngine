#ifndef MATH_RNG_HPP
#define MATH_RNG_HPP

#include "Math/Meta.hpp"

namespace BwatEngine::Math
{

#pragma region Declarations

    class RNG {
    public:
        RNG(unsigned int seed = 0) : m_seed(seed), m_position(0) {};

        // State modifiers

        ML_FUNC_DECL void ResetSeed(unsigned int seed, int position = 0) {m_seed = seed; m_position = position;}
        [[nodiscard]] ML_FUNC_DECL unsigned int GetSeed() const { return m_seed; }
        ML_FUNC_DECL void SetCurrentPosition(int position) { m_position = position;}
        [[nodiscard]] ML_FUNC_DECL int GetCurrentPosition() const {return m_position;}

        // RNGs
        [[nodiscard]] ML_FUNC_DECL unsigned int RollRandomUint32();
        [[nodiscard]] ML_FUNC_DECL unsigned short RollRandomUint16();
        [[nodiscard]] ML_FUNC_DECL unsigned char RollRandomByte();
        [[nodiscard]] ML_FUNC_DECL unsigned int RollRandomIntLessThan(unsigned int maxValue);
        [[nodiscard]] ML_FUNC_DECL int RollRandomIntInRange(int minValue, int maxValue);
        [[nodiscard]] ML_FUNC_DECL float RollRandomFloatZeroToOne();
        [[nodiscard]] ML_FUNC_DECL float RollRandomFloatInRange(float minValue, float maxValue);
        [[nodiscard]] ML_FUNC_DECL bool RollRandomChance(float probabilityOfReturningTrue);

    private:
        unsigned int m_seed;
        int m_position;
    };

#pragma endregion

#ifdef BMATH_IMPLEMENTATION
#pragma region Definitions

    ML_FUNC_DECL unsigned int RNG::RollRandomUint32()
    {
        return Get1dNoiseUint(m_position++, m_seed);
    }
    ML_FUNC_DECL unsigned short RNG::RollRandomUint16()
    {
        return static_cast<unsigned short>(Get1dNoiseUint(m_position++, m_seed));
    }
    ML_FUNC_DECL unsigned char RNG::RollRandomByte()
    {
        return static_cast<unsigned char>(Get1dNoiseUint(m_position++, m_seed));
    }
    ML_FUNC_DECL unsigned int RNG::RollRandomIntLessThan(unsigned int maxValue)
    {
        return static_cast<unsigned int>(Get1dNoiseZeroToOne(m_position++, m_seed) * maxValue);
    }
    ML_FUNC_DECL int RNG::RollRandomIntInRange(int minValue, int maxValue)
    {
        return minValue + static_cast<unsigned int>(Get1dNoiseZeroToOne(m_position++, m_seed) * maxValue);
    }
    ML_FUNC_DECL float RNG::RollRandomFloatZeroToOne()
    {
        return Get1dNoiseZeroToOne(m_position++, m_seed);
    }
    ML_FUNC_DECL float RNG::RollRandomFloatInRange(float minValue, float maxValue)
    {
        return minValue * Get1dNoiseZeroToOne(m_position++, m_seed) * maxValue;
    }
    ML_FUNC_DECL bool RNG::RollRandomChance(float probabilityOfReturningTrue)
    {
        return (Get1dNoiseZeroToOne(m_position++, m_seed) < probabilityOfReturningTrue) ? true : false;
    }

#pragma endregion
#endif //BMATH_IMPLEMENTATION

}
#endif //MATH_RNG_HPP