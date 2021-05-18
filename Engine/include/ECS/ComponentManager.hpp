#ifndef ENGINE_ECS_COMPONENT_MANAGER_HPP
#define ENGINE_ECS_COMPONENT_MANAGER_HPP
#include "ComponentArray.hpp"

#include <unordered_map>
#include <memory>

namespace BwatEngine
{
    class ComponentManager
    {
        std::unordered_map<const char*, ComponentTypeID> componentTypes{};

        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{};

        ComponentTypeID nextComponentType = 1;
    public:
        template<class C>
        void RegisterComponent()
        {
            const char* typeName = typeid(C).name();

            if(componentTypes.find(typeName) != componentTypes.end())
            {
                LogError("Registering component type more than once.");
                return;
            }

            componentTypes.insert({typeName, nextComponentType});
            componentArrays.insert({typeName, std::make_shared<ComponentArray<C>>()});

            nextComponentType++;
        }

        template<class C>
        ComponentTypeID GetComponentType()
        {
            const char* typeName = typeid(C).name();

            if(componentTypes.find(typeName) == componentTypes.end())
            {
                LogError("Component not registered before use.");
                return 0;
            }

            return componentTypes[typeName];
        }

        template<class C, typename... Args>
        void AddComponent(EntityID entity, Args&&... args)
        {
            if(!GetComponentType<C>())
                return;
            GetComponentArray<C>()->InsertData(entity, std::forward<Args>(args)...);
        }

        template<class C>
        void AddComponent(EntityID entity, C&& component)
        {
            if(!GetComponentType<C>())
                return;
            GetComponentArray<C>()->InsertData(entity, std::forward<C>(component));
        }

        template<class C>
        void AddComponent(EntityID entity)
        {
            if(!GetComponentType<C>())
                return;
            GetComponentArray<C>()->InsertData(entity);
        }

        template<class C>
        void RemoveComponent(EntityID entity)
        {
            if(!GetComponentType<C>())
                return;
            GetComponentArray<C>()->RemoveData(entity);
        }

        template<class C>
        C& GetComponent(EntityID entity)
        {
            if(!GetComponentType<C>())
            {
                // TODO: Better assertion
                LogFatal("Getting unregistered component.");
                throw std::runtime_error("ECS Crashed");
            }
            return GetComponentArray<C>()->GetData(entity);
        }

        template<class C>
        EntityID GetEntityIDFrom(C& component)
        {
            return GetComponentArray<C>()->GetEntityIDFrom(component);
        }

        void EntityDestroyed(EntityID entity)
        {            for (auto const& pair : componentArrays)
            {
                auto const& component = pair.second;

                component->EntityDestroyed(entity);
            }
        }

    private:
        template<class C>
        std::shared_ptr<ComponentArray<C>> GetComponentArray()
        {
            const char* typeName = typeid(C).name();
            if(componentTypes.find(typeName) == componentTypes.end())
            {
                LogError("Component not registered before use.");
                return nullptr;
            }
            return std::static_pointer_cast<ComponentArray<C>>(componentArrays[typeName]);
        }

    };
}

#endif //ENGINE_ECS_COMPONENT_MANAGER_HPP