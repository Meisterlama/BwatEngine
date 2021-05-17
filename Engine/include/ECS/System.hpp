#ifndef ENGINE_ECS_SYSTEM_HPP
#define ENGINE_ECS_SYSTEM_HPP

#include "ECS.hpp"
#include <set>

namespace BwatEngine
{
    struct SystemConfig
    {
        enum UpdateBehaviour
        {
            AlwaysUpdate,
            GameUpdate,
            ManualUpdate,
        };

        UpdateBehaviour updateBehaviour;
        unsigned short priority = 0;

        SystemConfig(UpdateBehaviour behaviour = AlwaysUpdate, unsigned short priority = 0)
        : updateBehaviour(behaviour)
        , priority(priority)
        {}
    };
    class System
    {
    public:
        virtual ~System() = default;
        virtual void Update() {};

        bool operator<(const System &rhs) const
        {
            return config.priority < rhs.config.priority;
        }

        SystemConfig config{};
        std::set<EntityID> entities{};
    };
}
#endif //ENGINE_ECS_SYSTEM_HPP
