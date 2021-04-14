#include "ECS/SystemManager.hpp"
#include "ECS/System.hpp"

namespace BwatEngine
{
    void SystemManager::EntityDestroyed(EntityID entity)
    {
        for (auto const& pair : systems)
        {
            auto const& system = pair.second;
            system->entities.erase(entity);
        }
    }

    void SystemManager::EntitySignatureChanged(EntityID entity, Signature entitySignature)
    {
        for (auto const& pair : systems)
        {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = signatures[type];

            if ((entitySignature & systemSignature) == systemSignature)
            {
                system->entities.insert(entity);
            }
            else
            {
                system->entities.erase(entity);
            }
        }
    }
}