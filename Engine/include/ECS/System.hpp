#ifndef ENGINE_ECS_SYSTEM_HPP
#define ENGINE_ECS_SYSTEM_HPP

#include "ECS.hpp"
#include <set>

namespace BwatEngine
{
    class System
    {
    public:
        std::set<EntityID> entities;
    };
}
#endif //ENGINE_ECS_SYSTEM_HPP
