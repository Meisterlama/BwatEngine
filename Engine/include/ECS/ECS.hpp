#ifndef ENGINE_ECS_ECS_HPP
#define ENGINE_ECS_ECS_HPP
#include <bitset>

namespace BwatEngine
{
    typedef uint32_t IDType;

    typedef IDType EntityID;
    static constexpr IDType MAX_ENTITIES = 10;

    typedef IDType ComponentTypeID;
    static constexpr ComponentTypeID MAX_COMPONENTS = 32;

    using Signature = std::bitset<MAX_COMPONENTS>;
}

#endif //ENGINE_ECS_ECS_HPP