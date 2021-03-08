#ifndef ENGINE_ECS_SYSTEM_HPP
#define ENGINE_ECS_SYSTEM_HPP

#include "Core.hpp"
#include <set>

namespace BwatEngine
{
    class System
    {
    public:
        std::set<EntityType> entities;
    };
}
#endif //ENGINE_ECS_SYSTEM_HPP
