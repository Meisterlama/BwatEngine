#ifndef ENGINE_ECS_SYSTEM_MANAGER_HPP
#define ENGINE_ECS_SYSTEM_MANAGER_HPP

#include "Core.hpp"
#include "System.hpp"

#include <unordered_map>

namespace BwatEngine
{
    class SystemManager
    {
        std::unordered_map<const char*, Signature> signatures{};
        std::unordered_map<const char*, std::shared_ptr<System>> systems{};
    public:
        template<typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            const char* typeName = typeid(T).name();
            assert(systems.find(typeName) == systems.end() && "Registering system more than once.");

            std::shared_ptr<T> system = std::make_shared<T>();
            systems.insert({typeName, system});
            return system;
        }

        template<typename T>
        void SetSignature(Signature signature)
        {
            const char* typeName = typeid(T).name();
            assert(systems.find(typeName) != systems.end() && "System used before registered.");
            signatures.insert({typeName, signature});
        }

				// It should be define in a .cpp
        void EntityDestroyed(Entity entity)
        {
            for (auto const& pair : systems)
            {
                auto const& system = pair.second;
                system->entities.erase(entity);
            }
        }

        void EntitySignatureChanged(Entity entity, Signature entitySignature)
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
    };
}

#endif //ENGINE_ECS_SYSTEM_MANAGER_HPP
