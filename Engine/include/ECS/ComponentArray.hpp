#ifndef ENGINE_ECS_COMPONENT_ARRAY_HPP
#define ENGINE_ECS_COMPONENT_ARRAY_HPP

#include "Core.hpp"
#include <cassert>
#include <unordered_map>
#include <vector>

namespace BwatEngine
{
    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity entity) = 0;
    };

    template<typename T>
    class ComponentArray: public IComponentArray
    {
        // TODO: Manage vector reallocation to handle more entities than default MAX_ENTITIES
        std::vector<T> componentArray{};
        std::unordered_map<Entity, size_t> entityToIndexMap{};
        std::unordered_map<size_t, Entity> indexToEntityMap{};
        size_t size{};

    public:
        ComponentArray()
        {
						// be careful of the memory impact of reserving MAX_ENTITIES
						// you should aim to reserve the average number of entities used in a game
            componentArray.reserve(MAX_ENTITIES);
        }

				// could use const for your component parameter ?
        void InsertData(Entity entity, T&& component)
        {
						// it's a pity that your assert doesn't use your logging system
						// and MAYBE you don't want to keep your assert in a release build
            assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component added to same entity more than once.");
            size_t newIndex = size;
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;
            if (size < componentArray.size())
                componentArray[newIndex] = component;
            else
                componentArray.push_back(component); // you should forward your component type
            size++;
        }

        void RemoveData(Entity entity)
        {
            assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Removing non-existent component.");

            size_t indexOfRemovedEntity = entityToIndexMap[entity];
            size_t indexOfLastElement = size - 1;
            componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

            Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
            entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            entityToIndexMap.erase(entity);
            indexToEntityMap.erase(indexOfLastElement);

            size--;
        }

        T& GetData(Entity entity)
        {
            assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Retrieving non-existent component.");
            return componentArray[entityToIndexMap[entity]];
        }

        void EntityDestroyed(Entity entity) override
        {
            if (entityToIndexMap.find(entity) != entityToIndexMap.end())
            {
                RemoveData(entity);
            }
        }
    };
}

#endif //ENGINE_ECS_COMPONENT_ARRAY_HPP
