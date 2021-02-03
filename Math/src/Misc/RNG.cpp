#include "Misc/RNG.hpp"
#include "Misc/Noise.hpp"

namespace Math
{
    [[nodiscard]] ML_FUNC_DECL unsigned int RNG::RollRandomUint32()
    {
        return Get1dNoiseUint(m_position++, m_seed);
    }
    [[nodiscard]] ML_FUNC_DECL unsigned short RNG::RollRandomUint16()
    {
        return static_cast<unsigned short>(Get1dNoiseUint(m_position++, m_seed));
    }
    [[nodiscard]] ML_FUNC_DECL unsigned char RNG::RollRandomByte()
    {
        return static_cast<unsigned char>(Get1dNoiseUint(m_position++, m_seed));
    }
    [[nodiscard]] ML_FUNC_DECL unsigned int RNG::RollRandomIntLessThan(unsigned int maxValue)
    {
        return static_cast<unsigned int>(Get1dNoiseZeroToOne(m_position++, m_seed) * maxValue);
    }
    [[nodiscard]] ML_FUNC_DECL int RNG::RollRandomIntInRange(int minValue, int maxValue)
    {
        return minValue + static_cast<unsigned int>(Get1dNoiseZeroToOne(m_position++, m_seed) * maxValue);
    }
    [[nodiscard]] ML_FUNC_DECL float RNG::RollRandomFloatZeroToOne()
    {
        return Get1dNoiseZeroToOne(m_position++, m_seed);
    }
    [[nodiscard]] ML_FUNC_DECL float RNG::RollRandomFloatInRange(float minValue, float maxValue)
    {
        return minValue * Get1dNoiseZeroToOne(m_position++, m_seed) * maxValue;
    }
    [[nodiscard]] ML_FUNC_DECL bool RNG::RollRandomChance(float probabilityOfReturningTrue)
    {
        return (Get1dNoiseZeroToOne(m_position++, m_seed) < probabilityOfReturningTrue);
    }
}