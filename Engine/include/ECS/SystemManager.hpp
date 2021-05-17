#ifndef ENGINE_ECS_SYSTEM_MANAGER_HPP
#define ENGINE_ECS_SYSTEM_MANAGER_HPP

#include "ECS.hpp"
#include "Debug/Logger.hpp"
#include "ECS/System.hpp"
#include <unordered_map>
#include <memory>
#include <queue>

namespace BwatEngine
{
    class System;
    class SystemManager
    {
        std::unordered_map<const char*, Signature> signatures{};
        std::unordered_map<const char*, std::shared_ptr<System>> systems{};
    public:
        void DestroySystems()
        {
            systems.clear();
            signatures.clear();
        }
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
        std::shared_ptr<S> GetSystem()
        {
            const char* typeName = typeid(S).name();
            auto result = systems.find(typeName);

            if (result == systems.end())
            {
                LogError("Register your system before using it !");
                return nullptr;
            }
            return std::dynamic_pointer_cast<S>(result->second);
        }

        template<typename S>
        void SetSystemConfig(SystemConfig config)
        {
            const char* typeName = typeid(S).name();
            auto result = systems.find(typeName);
            if ( result == systems.end())
            {
                LogError("Register your system before using it !");
                return;
            }
            result->second->config = config;
        }

        template<class S>
        constexpr void SetSignature(Signature signature)
        {
            const char* typeName = typeid(S).name();
            if(systems.find(typeName) == systems.end())
            {
                LogError("Register your system before using it !");
                return;
            }
            signatures.insert({typeName, signature});
        }

        void UpdateSystems(bool gameUpdate)
        {
            constexpr auto cmp = [](const std::shared_ptr<System>& lhs, const std::shared_ptr<System>& rhs) { return (*lhs) < (*rhs);};
            std::priority_queue<std::shared_ptr<System>, std::vector<std::shared_ptr<System>>, decltype(cmp)> queue(cmp);
            for (auto& pair : systems)
            {
                queue.push(pair.second);
            }

            while (!queue.empty())
            {
                auto systemPtr = queue.top();
                switch (systemPtr->config.updateBehaviour)
                {
                    case SystemConfig::AlwaysUpdate:
                        systemPtr->Update();
                        break;
                    case SystemConfig::GameUpdate:
                        if (gameUpdate) systemPtr->Update();
                        break;
                    case SystemConfig::ManualUpdate:
                        break;
                }
                queue.pop();
            }
        }

        void EntityDestroyed(EntityID entity);

        void EntitySignatureChanged(EntityID entity, Signature entitySignature);
    };
}

#endif //ENGINE_ECS_SYSTEM_MANAGER_HPP