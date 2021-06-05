#ifndef ENGINE_ECS_COMPONENT_ARRAY_HPP
#define ENGINE_ECS_COMPONENT_ARRAY_HPP

#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace BwatEngine
{
    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(EntityID entity) = 0;
    };

    template<typename C>
    class ComponentArray: public IComponentArray
    {
        // TODO: Manage vector reallocation to handle more entities than default MAX_ENTITIES
        std::vector<C> componentArray{};
        std::unordered_map<EntityID, size_t> entityToIndexMap{};
        std::unordered_map<size_t, EntityID> indexToEntityMap{};

    public:
        ComponentArray()
        {
            componentArray.reserve(MAX_ENTITIES);
        }

        template<typename... Args>
        void InsertData(EntityID entity, Args&&... args)
        {
            if(entityToIndexMap.find(entity) != entityToIndexMap.end())
            {
                LogError("[ECS] Component added to same entity more than once.");
                return;
            }
            size_t newIndex = componentArray.size();
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;

            componentArray.emplace_back(args...);
        }

        void InsertData(EntityID entity, C&& component)
        {
            if(entityToIndexMap.find(entity) != entityToIndexMap.end())
            {
                LogError("[ECS] Component added to same entity more than once.");
                return;
            }
            size_t newIndex = componentArray.size();
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;

            componentArray.push_back(component);
        }

        void InsertData(EntityID entity)
        {
            if(entityToIndexMap.find(entity) != entityToIndexMap.end())
            {
                LogError("[ECS] Component added to same entity more than once.");
                return;
            }
            size_t newIndex = componentArray.size();
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;

            componentArray.emplace_back();
        }

        void RemoveData(EntityID entity)
        {
            if(entityToIndexMap.find(entity) == entityToIndexMap.end())
            {
                LogError("[ECS] Removing non-existent component.");
                return;
            }

            size_t indexOfRemovedEntity = entityToIndexMap[entity];
            size_t indexOfLastElement = componentArray.size() - 1;

            auto itLast = (componentArray.begin() + indexOfLastElement);
            auto itRemoved = (componentArray.begin() + indexOfRemovedEntity);
            std::swap(itLast, itRemoved);
            componentArray.pop_back();

            EntityID entityOfLastElement = indexToEntityMap[indexOfLastElement];
            entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            entityToIndexMap.erase(entity);
            indexToEntityMap.erase(indexOfLastElement);
        }

        C& GetData(EntityID entity)
        {
            if(entityToIndexMap.find(entity) == entityToIndexMap.end())
            {
                // TODO: Better assertion
                LogFatal("[ECS] Retrieving non-existent component.");
                throw std::runtime_error("ECS Crashed");
            }
            return componentArray[entityToIndexMap[entity]];
        }

        EntityID GetEntityIDFrom(C& component)
        {
            for (size_t i = 0; i < componentArray.size(); i++)
            {
                if (&componentArray[i] == &component)
                    return indexToEntityMap[i];
            }
            return 0;
        }

        void EntityDestroyed(EntityID entity) override
        {
            if (entityToIndexMap.find(entity) != entityToIndexMap.end())
            {
                RemoveData(entity);
            }
        }
    };
}

#endif //ENGINE_ECS_COMPONENT_ARRAY_HPP
