#ifndef ENGINE_CORE_HPP
#define ENGINE_CORE_HPP

//TODO: Create logic for dll creation
#ifdef WIN32
#define BWATAPI
#else
#define BWATAPI
#endif

#include <bitset>

namespace BwatEngine
{
// ECS
    using Entity = uint32_t;

    static constexpr Entity MAX_ENTITIES = 10000;

    using ComponentType = uint8_t;

    static constexpr ComponentType MAX_COMPONENTS = 32;

    using Signature = std::bitset<MAX_COMPONENTS>;
}


#endif //ENGINE_CORE_HPP