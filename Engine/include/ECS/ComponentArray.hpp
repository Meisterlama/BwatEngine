#ifndef ENGINE_ECS_COMPONENT_ARRAY_HPP
#define ENGINE_ECS_COMPONENT_ARRAY_HPP

#include "Core.hpp"
#include <cassert>
#include <unordered_map>
#include <array>

namespace BwatEngine
{
    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(EntityType entity) = 0;
    };

    template<typename T>
    class ComponentArray: public IComponentArray
    {
        std::array<T, MAX_ENTITIES> componentArray{};
        std::unordered_map<EntityType, size_t> entityToIndexMap{};
        std::unordered_map<size_t, EntityType> indexToEntityMap{};
        size_t size{};

    public:
        void InsertData(EntityType entity, T component)
        {
            assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component added to same entity more than once.");
            size_t newIndex = size;
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;
            componentArray[newIndex] = component;
            size++;
        }

        void RemoveData(EntityType entity)
        {
            assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Removing non-existent component.");

            size_t indexOfRemovedEntity = entityToIndexMap[entity];
            size_t indexOfLastElement = size - 1;
            componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

            EntityType entityOfLastElement = indexToEntityMap[indexOfLastElement];
            entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            entityToIndexMap.erase(entity);
            indexToEntityMap.erase(indexOfLastElement);

            size--;
        }

        T& GetData(EntityType entity)
        {
            assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Retrieving non-existent component.");
            return componentArray[entityToIndexMap[entity]];
        }

        void EntityDestroyed(EntityType entity) override
        {
            if (entityToIndexMap.find(entity) != entityToIndexMap.end())
            {
                RemoveData(entity);
            }
        }
    };
}

#endif //ENGINE_ECS_COMPONENT_ARRAY_HPP
