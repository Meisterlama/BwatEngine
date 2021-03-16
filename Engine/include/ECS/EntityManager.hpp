#ifndef ENGINE_ECS_ENTITY_MANAGER_HPP
#define ENGINE_ECS_ENTITY_MANAGER_HPP
#include "Core.hpp"
#include "Debug/Logger.hpp"
#include <array>
#include <queue>
#include <cassert>

namespace BwatEngine
{
    class EntityManager
    {
        std::queue<Entity> availableEntities{};
        Entity nextEntity{};
        std::array<Signature, MAX_ENTITIES> signatures{};
        int livingEntityCount{};

    public:
        EntityManager()
        {}

        Entity CreateEntity()
        {
            assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");
            Entity id = nextEntity;
            if (!availableEntities.empty())
            {
                id = availableEntities.front();
                availableEntities.pop();
            }
            else
            {
                nextEntity++;
            }
            livingEntityCount++;

            return id;
        }

        void DestroyEntity(Entity entity)
        {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            signatures[entity].reset();

            availableEntities.push(entity);
            livingEntityCount--;
        }

        void SetSignature(Entity entity, Signature signature)
        {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            signatures[entity] = signature;
        }

        Signature GetSignature(Entity entity)
        {
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            return signatures[entity];
        }
    };
}

#endif //ENGINE_ECS_ENTITY_MANAGER_HPP