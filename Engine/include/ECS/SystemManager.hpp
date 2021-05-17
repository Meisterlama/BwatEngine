#ifndef ENGINE_ECS_SYSTEM_MANAGER_HPP
#define ENGINE_ECS_SYSTEM_MANAGER_HPP

#include "ECS.hpp"
#include "Debug/Logger.hpp"
#include <unordered_map>
#include <memory>

namespace BwatEngine
{
    class System;
    class SystemManager
    {
        std::unordered_map<const char*, Signature> signatures{};
        std::unordered_map<const char*, std::shared_ptr<System>> systems{};
    public:
        template<class S, class... Args>
        std::shared_ptr<S> RegisterSystem(Args&&... args)
        {
            const char* typeName = typeid(S).name();
            if (systems.find(typeName) != systems.end())
            {
                LogError("Registering system more than once.");
                return nullptr;
            }

            std::shared_ptr<S> system = std::make_shared<S>(args...);
            systems.insert({typeName, system});
            return system;
        }

        template<class S>
        void SetSignature(Signature signature)
        {
            const char* typeName = typeid(S).name();
            if(systems.find(typeName) == systems.end())
            {
                LogError("Register your system before using it !");
                return;
            }
            signatures.insert({typeName, signature});
        }

        void EntityDestroyed(EntityID entity);

        void EntitySignatureChanged(EntityID entity, Signature entitySignature);
    };
}

#endif //ENGINE_ECS_SYSTEM_MANAGER_HPP