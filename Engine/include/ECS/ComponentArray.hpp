#ifndef ENGINE_ECS_COMPONENT_ARRAY_HPP
#define ENGINE_ECS_COMPONENT_ARRAY_HPP

#include <unordered_map>
#include <vector>
#include <stdexcept>

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
        size_t size{};

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
                LogError("Component added to same entity more than once.");
                return;
            }
            size_t newIndex = size;
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;
            if (size < componentArray.size())
                componentArray[newIndex] = std::move(C{std::forward<Args>(args)...});
            else
                componentArray.emplace_back(args...);
            size++;
        }

        void InsertData(EntityID entity, C&& component)
        {
            if(entityToIndexMap.find(entity) != entityToIndexMap.end())
            {
                LogError("Component added to same entity more than once.");
                return;
            }            size_t newIndex = size;
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;
            if (size < componentArray.size())
                componentArray[newIndex] = component;
            else
                componentArray.push_back(component);
            size++;
        }

        void InsertData(EntityID entity)
        {
            if(entityToIndexMap.find(entity) != entityToIndexMap.end())
            {
                LogError("Component added to same entity more than once.");
                return;
            }            size_t newIndex = size;
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;
            if (size < componentArray.size())
                componentArray[newIndex] = std::move<C>({});
            else
                componentArray.emplace_back();
            size++;
        }

        void RemoveData(EntityID entity)
        {
            if(entityToIndexMap.find(entity) == entityToIndexMap.end())
            {
                LogError("Removing non-existent component.");
                return;
            }

            size_t indexOfRemovedEntity = entityToIndexMap[entity];
            size_t indexOfLastElement = size - 1;
            componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];
            componentArray.pop_back();

            EntityID entityOfLastElement = indexToEntityMap[indexOfLastElement];
            entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            entityToIndexMap.erase(entity);
            indexToEntityMap.erase(indexOfLastElement);

            size--;
        }

        C& GetData(EntityID entity)
        {
            if(entityToIndexMap.find(entity) == entityToIndexMap.end())
            {
                // TODO: Better assertion
                LogFatal("Retrieving non-existent component.");
                throw std::runtime_error("ECS Crashed");
            }
            return componentArray[entityToIndexMap[entity]];
        }

        EntityID GetEntityIDFrom(C& component)
        {
            for (size_t i = 0; i < size; i++)
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
